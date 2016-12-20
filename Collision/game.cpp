/*************************************************************************
 * game.cpp for project Collision
 * Author : lzh
 * Modifier : Shlw lzh Shlw lzh lziad lzh lziad lzh
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
ALuint uBGMBuf;
// the duration of the files
double dpDuration[100];
// the minimum heap records when each source will be valid to play sounds
// the last two digits are the index of the source
// **ATTENTION** Because of the above reason, the maximum of files must be 100
//               or it would trouble a lot.
std::priority_queue<long, std::vector<long>, std::greater<long> > qSrcQueue;
// the wave files which cannot be played on time
int npSoundQueue[1000];
int nSndQuePtr;
// volumes
ALfloat fBGMVol, fEffVol;

ALCdevice *pDevice;
ALCcontext *pContext;

// The result is the wav file's duration in seconds.
double CalWAVDuration(ALsizei size, ALfloat freq, ALenum format) {
    double coef = 1.0;
    switch (format) {
        case AL_FORMAT_MONO8:
            coef = 1.0;
            break;
        case AL_FORMAT_MONO16:
            coef = 2.0;
            break;
        case AL_FORMAT_STEREO8:
            coef = 2.0;
            break;
        case AL_FORMAT_STEREO16:
            coef = 4.0;
            break;
        default:
            ;
    }
    return (double)size / freq / coef;
}

Audio* Audio::GetAudio() {
    static Audio msAudio;
    return &msAudio;
}

void Audio::LoadFile(int index) {
    ALuint  buffer, source;
    ALenum  error;

    ALenum  format;
    ALvoid  *data=NULL;

    ALsizei size;
    ALfloat freq;

    if (index < 0 || index >= 100) {
        throw ERROR_UNKNOWN_SOUND;
    } else if (upBufList[index]) {
        // the source has been already loaded, simply play it
        buffer = upBufList[index];
    } else {
        // else load the file
        alGenBuffers(1, &buffer);
        data = alutLoadMemoryFromFile(cpSndFileList[index], &format, &size, &freq);
        if (NULL == data)
            throw FILE_NOT_FOUND;

        alBufferData(buffer, format, data, size, freq);
        upBufList[index] = buffer;
        dpDuration[index] = CalWAVDuration(size, freq, format);
    }

    // find the next free source
    long lNxtSrc = qSrcQueue.top();
    if (lNxtSrc / 1e5 > dLastClock) {
        // no vacant seats
        if (nSndQuePtr < 1000)
            // if 1000+100 sources are not even enough, ignore it
            npSoundQueue[nSndQuePtr++] = index;
        return ;
    } else {
        source = upSrcList[lNxtSrc % 100];
    }

    // be sure that the source is cleaned
    alSourcei(source, AL_BUFFER, AL_NONE);
    alSourcei(source, AL_BUFFER, buffer);
    // set volume
    alSourcef(source, AL_GAIN, fEffVol);

    error = alGetError();
    if (error != ALUT_ERROR_NO_ERROR) {
        fprintf(stderr, "Error when playing wav file: %s\n", alGetString(error));
        throw ERROR_OPENAL;
    }

    alSourcePlay(source);
    qSrcQueue.pop();
    // add 100 ms for delay
    qSrcQueue.push(lNxtSrc % 100 + 10000 +
                   long((dpDuration[index] + dLastClock) * 1e3) * 100);

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
    if (NULL == data)
        throw FILE_NOT_FOUND;

    alBufferData(buffer, format, data, size, freq);

    alSourcei(source, AL_BUFFER, buffer);
    // loop
    alSourcei(source, AL_LOOPING, true);
    alSourcef(source, AL_GAIN, fBGMVol);

    error = alGetError();
    if (error != ALUT_ERROR_NO_ERROR) {
        fprintf(stderr, "Error when playing wav file: %s\n", alGetString(error));
        throw ERROR_OPENAL;
    }

    alSourcePlay(source);

    free(data);

    uBGMBuf = buffer;

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
    memset(dpDuration, 0, sizeof(dpDuration));
    memset(npSoundQueue, 0, sizeof(npSoundQueue));

    memset(bpCrashing, 0, sizeof(bpCrashing));

    nSndQuePtr = 0;
    fBGMVol = fEffVol = 1.0;

    for (int i = 1; i < 100; ++i)
        qSrcQueue.push(i);

    // init openAL
    pDevice = alcOpenDevice(NULL);
    pContext = alcCreateContext(pDevice, NULL);
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
#ifdef DEBUG
    std::cout << nLastSecond << ' ' << nModelTot << ' ' << nObjectTot << std::endl;
    printf("%ds:\n",nLastSecond);
    float E = 0.0;
    float dets = 0.0;
    for (int i = 0; i < nObjectTot; i++)
    {
        glm::mat3 I = glm::mat3(*oppObjectList[i] -> mpFrame) *
            *mppModelList[oppObjectList[i]->nModelType]->mMomentOfInertia *
            glm::transpose(glm::mat3(*oppObjectList[i] -> mpFrame));
        glm::vec3 v = *oppObjectList[i]->vpSpeed;
        glm::vec3 w = glm::inverse(I)* *oppObjectList[i]->vpAngularMomentum;
        float e = 0.5 * mppModelList[oppObjectList[i]->nModelType]->fMass * glm::dot(v, v) +
                0.5 * glm::dot(w, *oppObjectList[i] -> vpAngularMomentum);
        dets = glm::determinant(*oppObjectList[i] -> mpFrame);
        // printf("object%d:\n v = (%f, %f, %f),\n w = (%f, %f, %f),\n Ek = %f, det = %f\n",
        //        i, v[0], v[1], v[2], w[0], w[1], w[2], e, dets);
        E += e;
    }
    printf("total: Ek = %f\n", E);
#endif
    return ;
}

void GameCleanUp()
{
    for (int i = 0; i < 100; i++)
        alSourceStop(upSrcList[i]);
    // delete buffers and sources
    for (int i = 0; i < 100; ++i)
        if (upBufList[i])
            alDeleteBuffers(1, upBufList+i);
    alDeleteBuffers(1, &uBGMBuf);
    alDeleteSources(100, upSrcList);
    // shutdown openAL
    alcMakeContextCurrent(NULL);
    alcDestroyContext(pContext);
    alcCloseDevice(pDevice);

    return ;
}
