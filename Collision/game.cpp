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
ALuint upSrcList[100];
// current playing source
ALuint uCurSource;

Audio* Audio::GetAudio() {
    static Audio msAudio;
    return &msAudio;
}

void Audio::LoadFile(int index) {
    // waiting until the current playing source stops
    if (uCurSource != AL_NONE) {
        ALint status;
        alGetSourcei(uCurSource, AL_SOURCE_STATE, &status);
        if (status == AL_PLAYING)
            return ;
    }

    if (index < 0 || index >= 100) {
        throw ERROR_UNKNOWN_SOUND;
    } else if (upSrcList[index]) {
        // the source has been already loaded, simply play it
        alSourcePlay(upSrcList[index]);
        // set the current playing source
        uCurSource = upSrcList[index];
        return ;
    }
    // else load the file

    ALuint  buffer, source;
    ALenum  error;

    ALenum  format;
    ALvoid  *data;

    ALsizei size;
    ALfloat freq;

    // load the wav file
    alGenBuffers(1, &buffer);
    data = alutLoadMemoryFromFile(cpSndFileList[index], &format, &size, &freq);
    alBufferData(buffer, format, data, size, freq);
    alGenSources(1, &source);

    if (buffer == AL_NONE) {
        alutExit();
        throw FILE_NOT_FOUND;
    }

    alSourcei(source, AL_BUFFER, buffer);
    // TODO: alSourcefv(source, AL_POSITION, [SourcePosition]);

    error = alGetError();
    if (error != ALUT_ERROR_NO_ERROR) {
        fprintf(stderr, "Error when playing wav file: %s\n", alGetString(error));
        alutExit();
        throw ERROR_OPENAL;
    }
    alSourcePlay(source);

    // add the source and set the current playing source
    uCurSource = upSrcList[index] = source;
    
    // *alutLoadMemoryFromFile* allocates memory for *data*,
    // so delete it after use.
    delete data;

    return ;
}

void Audio::LoadBGM() {
    ALuint  buffer, source;
    ALenum  error;

    ALenum  format;
    ALvoid  *data;

    ALsizei size;
    ALfloat freq;
    
    alGenBuffers(1, &buffer);
    data = alutLoadMemoryFromFile("bgm.wav", &format, &size, &freq);
    alBufferData(buffer, format, data, size, freq);
    alGenSources(1, &source);

    if (buffer == AL_NONE) {
        alutExit();
        throw FILE_NOT_FOUND;
    }

    alSourcei(source, AL_BUFFER, buffer);
    // loop
    alSourcei(source, AL_LOOPING, true);

    error = alGetError();
    if (error != ALUT_ERROR_NO_ERROR) {
        fprintf(stderr, "Error when playing wav file: %s\n", alGetString(error));
        alutExit();
        throw ERROR_OPENAL;
    }
    alSourcePlay(source);
    
    delete data;
    
    return ;
}

void GameInit()
{
    memset(cpModFileList, 0, sizeof(cpModFileList));
    memset(npTypeList, 0, sizeof(npTypeList));
    memset(cpSndFileList, 0, sizeof(cpSndFileList));
    memset(upSrcList, 0, sizeof(upSrcList));

    // init openAL
    ALCdevice *pDevice = alcOpenDevice(NULL);
    ALCcontext *pContext = alcCreateContext(pDevice, NULL);
    alcMakeContextCurrent(pContext);
    uCurSource = AL_NONE;

    // read wav files
    FILE *fpSndEff = fopen("SoundEff.txt", "r");
    char cpSndFile[256];
    // only record first 100 paths
    for (nSndFileCount = 0; nSndFileCount < 100 &&
         fscanf(fpSndEff, "%[^\n]\n", cpSndFile) != EOF; ++nSndFileCount)
        memcpy(cpSndFileList[nSndFileCount], cpSndFile,
               strlen(cpSndFile) * sizeof(char));
    fclose(fpSndEff);

    // play bgm
    Audio::GetAudio()->LoadBGM();
    
    return ;
}

void GameMove(GLFWwindow* w, double x, double y)
{
    if (++nPtr % 10 == 0)
    nPtr = 0;
    dpPos[nPtr][0] = x; dpPos[nPtr][1] = y;
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
    *oppObjectList[nObjectTot++]->vpAngularMomentum =glm::vec3((x2-x1)*0.05, (y2-y1)*0.05, (z2-z1)*0.05);

    return ;
}

void GameSecond()
{
    std::cout << nLastSecond << ' ' << nModelTot << ' ' << nObjectTot << std::endl;
    return ;
}

void GameCleanUp()
{
    // shutdown openAL
    ALCcontext *pContext = alcGetCurrentContext();
    ALCdevice *pDevice = alcGetContextsDevice(pContext);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(pContext);
    alcCloseDevice(pDevice);
    alutExit;
    
    return ;

}
