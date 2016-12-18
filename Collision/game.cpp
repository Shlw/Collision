/*************************************************************************
 * game.cpp for project Collision
 * Author : lzh
 * Modifier : Shlw lzh Shlw lzh lziad lzh lziad
 * Description : Source file to implement Game, which handles the game
 * logic, that is, to determine when to release a new object and something
 * like that.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

// path and type of the model files which are already loaded
char   cpModFileList[100][256];
int    npTypeList[100];
// path of the files of the sound files which are already loaded
char   cpSndFileList[100][256];
int    nSndFileCount;
// buffers and sources
ALuint upBufList[100], upSrcList[100];
// pointer to the next free source
// **ATTENTION** upSrcList[0] is reserved for playing bgm,
// so nSrcPtr will NEVER equals to 0.
int nSrcPtr;
// volumes
ALfloat fBGMVol, fEffVol;

Audio* Audio::GetAudio() {
    static Audio msAudio;
    return &msAudio;
}

void Audio::LoadFile(int index) {
    ALuint  buffer, source;
    ALenum  error;
    
    ALenum  format, state = AL_PLAYING;
    ALvoid  *data=NULL;
    
    ALsizei size;
    ALfloat freq;
    
    int i;
    
    if (index < 0 || index >= 100) {
        throw ERROR_UNKNOWN_SOUND;
    } else if (upBufList[index]) {
        // the source has been already loaded, simply play it
        buffer = upBufList[index];
    } else {
        // else load the file
        alGenBuffers(1, &buffer);
        data = alutLoadMemoryFromFile(cpSndFileList[index], &format, &size, &freq);
        if (NULL == data) {
            alutExit();
            throw FILE_NOT_FOUND;
        }
        alBufferData(buffer, format, data, size, freq);
        upBufList[index] = buffer;
    }
    
    // find the next free source
    for (i = 1; i < 100 && state == AL_PLAYING; ++i, ++nSrcPtr) {
        if (nSrcPtr >= 100)
            nSrcPtr = 1;
        source = upSrcList[nSrcPtr];
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    }
    
    if (i == 100) {
        fprintf(stderr, "Error when playing wav file: Out of memory\n");
        throw ERROR_OPENAL;
    }
    
    // be sure that the source is cleaned
    alSourcei(source, AL_BUFFER, AL_NONE);
    alSourcei(source, AL_BUFFER, buffer);
    // set volume
    alSourcef(source, AL_GAIN, fEffVol);
    
    error = alGetError();
    if (error != ALUT_ERROR_NO_ERROR) {
        fprintf(stderr, "Error when playing wav file: %s\n", alGetString(error));
        alutExit();
        throw ERROR_OPENAL;
    }
    
    alSourcePlay(source);
    
    // *alutLoadMemoryFromFile* allocates memory for *data*,
    // so free it after use.
    free(data);
    
    return ;
}

void Audio::LoadBGM() {
    ALuint  buffer, source = upSrcList[0];
    ALenum  error;

    ALenum  format;
    ALvoid  *data=NULL;

    ALsizei size;
    ALfloat freq;

    alGenBuffers(1, &buffer);
    data = alutLoadMemoryFromFile("bgm.wav", &format, &size, &freq);
    if (NULL == data) {
        alutExit();
        throw FILE_NOT_FOUND;
    }
    alBufferData(buffer, format, data, size, freq);
    
    alSourcei(source, AL_BUFFER, buffer);
    // loop
    alSourcei(source, AL_LOOPING, true);
    alSourcef(source, AL_GAIN, fBGMVol);
    
    error = alGetError();
    if (error != ALUT_ERROR_NO_ERROR) {
        fprintf(stderr, "Error when playing wav file: %s\n", alGetString(error));
        alutExit();
        throw ERROR_OPENAL;
    }
    
    alSourcePlay(source);

    free(data);

    return ;
}

void Audio::SetVolume() {
    alSourcef(upSrcList[0], AL_GAIN, fBGMVol);
    for (int i = 1; i < 100; ++i)
        alSourcef(upSrcList[i], AL_GAIN, fEffVol);
}

void GameInit()
{
    memset(cpModFileList, 0, sizeof(cpModFileList));
    memset(npTypeList, 0, sizeof(npTypeList));
    memset(cpSndFileList, 0, sizeof(cpSndFileList));
    memset(upBufList, 0, sizeof(upBufList));
    memset(upSrcList, 0, sizeof(upSrcList));
    
    memset(bpCrashing, 0, sizeof(bpCrashing));
    
    nSrcPtr = 1;
    fBGMVol = fEffVol = 1.0;

    // init openAL
    ALCdevice *pDevice = alcOpenDevice(NULL);
    ALCcontext *pContext = alcCreateContext(pDevice, NULL);
    alcMakeContextCurrent(pContext);

    // read wav files
    FILE *fpSndEff = fopen("SoundEff.txt", "r");
    char cpSndFile[256];
    // only record first 100 paths
    for (nSndFileCount = 0; nSndFileCount < 100 &&
         fscanf(fpSndEff, "%[^\n]\n", cpSndFile) != EOF; ++nSndFileCount)
        memcpy(cpSndFileList[nSndFileCount], cpSndFile,
               strlen(cpSndFile) * sizeof(char));
    fclose(fpSndEff);
    
    // allocate memory for sources
    alGenSources(100, upSrcList);

    // play bgm
    Audio::GetAudio()->LoadBGM();

    return ;
}

void GameMove(GLFWwindow* w, double x, double y)
{
    return ;
}

void GameDrag(GLFWwindow* w, int c, const char** p)
{
    int i, nType, nPrv;
    bool bFound = false;
    double x1, x2, y1, y2, z1, z2;
    for (i = 0; i < 100 && !bFound && strlen(cpModFileList[i]) > 0; ++i)
        // only consider the first file
        if (strcmp(cpModFileList[i], p[0]) == 0)
            bFound = true;
    if (bFound) {
        // the model has been already loaded
        nType = npTypeList[i-1];
    } else if (i == 100) {
        // no vacant seats for the new object
        throw ERROR_TOO_MANY_OBJ;
    } else {
        // add the path first
        memcpy(cpModFileList[i], p[0], strlen(p[0]) * sizeof(char));
        nType = npTypeList[i] = ReadFiles(p[0]);
    }
    oppObjectList[nObjectTot] = new Object(nType, 0.0, 0.0, 0.0);
    // convert mouse coordinates to OpenGL coordinates
    UnProjectNow(dLastMouseX, dLastMouseY, 0.95, &x2, &y2, &z2);
    UnProjectNow(dLastMouseX, dLastMouseY, 0.9, &x1, &y1, &z1);

    // set the position
    *oppObjectList[nObjectTot]->mpFrame = glm::inverse(mModelTransformMat);
    (*oppObjectList[nObjectTot]->mpFrame)[3] = glm::vec4(x1, y1, z1, 1);

    // set the speed
    *oppObjectList[nObjectTot]->vpSpeed = glm::vec3(x2-x1, y2-y1, z2-z1);
    *oppObjectList[nObjectTot++]->vpAngularMomentum =glm::vec3((x2-x1)*0.01, (y2-y1)*0.01, (z2-z1)*0.01);

    return ;
}

void GameSecond()
{
    std::cout << nLastSecond << ' ' << nModelTot << ' ' << nObjectTot << std::endl;
    return ;
}

void GameCleanUp()
{
    // delete buffers and sources
    for (int i = 0; i < 100; ++i)
        if (upBufList[i])
            alDeleteBuffers(1, upBufList+i);
    alDeleteSources(100, upSrcList);
    // shutdown openAL
    ALCcontext *pContext = alcGetCurrentContext();
    ALCdevice *pDevice = alcGetContextsDevice(pContext);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(pContext);
    alcCloseDevice(pDevice);
    alutExit;

    return ;

}
