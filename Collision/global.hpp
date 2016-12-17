/*************************************************************************
 * global.hpp for project Collision
 * Author : lzh
 * Modifier : Shlw lzh Shlw lzh lziad Shlw lzh lziad
 * Description : Global header for the whole project, including
 * inclusion of public headers and declarations.
 ************************************************************************/

// Check whether included
#ifndef CL_GLOBAL_HPP

#define CL_GLOBAL_HPP

// Include public headers
#include <cstdlib>
#include <cmath>
#include <climits>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <vector>

#include <jpeglib.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <AL/alut.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Exception Flags
#define ERROR_UNKNOWN_MODEL 0x0001
#define FILE_NOT_FOUND 0x0002
#define ERROR_TOO_MANY_OBJ 0x0003
#define ERROR_UNKNOWN_SOUND 0x0004
#define ERROR_OPENAL 0x0005

// class declarations
class Point;
class Triangle;
class Model;
class Object;
class Audio;

// typedef definitions
typedef glm::vec2* PVec2;
typedef glm::vec3* PVec3;
typedef glm::vec4* PVec4;
typedef glm::mat4* PMat4;
typedef Point* PPoint;
typedef Triangle* PTriangle;
typedef Model* PModel;
typedef Object* PObject;

// complementary functions
PPoint MultPoint(PMat4 matrix,PPoint p);
PTriangle MultTriangle(PMat4 matrix,PTriangle cone);
bool IsIntersect(PTriangle a,PVec4 tp,PVec3 vdir);
bool IsInArea(PTriangle a,PVec4 tp);

// point class represents the still point in local coordinate system
class Point{
public:
    int nFlag;
    PVec4 vpCoordinate;
    PVec4 vpColor;
    PVec2 vpTexture;

    Point();
    Point(PPoint example);
    Point(
        float x,float y,float z,
        float r,float g,float b,float alpha
    );
    ~Point();

    void DrawVertex();
};

// triangle class represents the still triangle(cone) in local coordinate system
class Triangle{
public:
    PPoint pppVertex[3];
    PVec4 vpNormalVector;

    Triangle();
    Triangle(PPoint a,PPoint b,PPoint c);
    Triangle(PPoint a,PPoint b,PPoint c,PVec4 v);
    ~Triangle();

    void Draw();
};

// model class represents the still model in local coordinate system
class Model{
public:
    int nLength; // the number of triangular cones
    PTriangle* tppCone; // the point array of triangle pointers
    float fVolume,fElastic,fMass,fMaxRadius;
    glm::mat3* mMomentOfInertia;

    Model();
    ~Model();

    void Draw();
};

// object class contains
// the matrix(mFrame) to transform between local and global coordinate system
// and several indispensable descriptive aspect of the object
class Object{
public:
    int nModelType;
    PMat4 mpFrame;
    PVec3 vpSpeed;
    PVec3 vpAngularMomentum;
    float fMomentInertia;

    Object();
    Object(int model,float vx=0,float vy=0,float vz=0,float mx=0,float my=0,float mz=0);
    ~Object();

    PTriangle IsInside(PVec4 tp,PVec3 vdir=NULL);
    //ymw changed tp from PPoint to PVec4

    void Draw();
    void Update();
};

// audio class contains functions to play wav files
class Audio {
private:
    // The following functions are private to forbid the following uses:
    /// Audio boo = Audio::GetAudio();
    /// Audio booo = boo; (or rather *Audio booo;* without initialize)
    // and in this way neither &boo nor &booo equals to &msAudio.
    Audio() {};
    Audio(const Audio &);
    Audio & operator =(const Audio &);
public:
    ~Audio() {};

    // construct and return a single instance
    static Audio* GetAudio();

    // load and play *.wav
    void LoadFile(int index);

    // load the bgm file
    void LoadBGM();
};

extern int nModelTot;
extern int nObjectTot;
extern PModel mppModelList[100];
extern PObject oppObjectList[100];

// Declarations of global variables defined in .cpp files

// extern int nWindowFlags;
extern int nInitWindowWidth;
extern int nInitWindowHeight;
extern const char* cpWindowTitle;

extern double dLastClock, dLastLastClock;
extern double dLastMouseX, dLastMouseY;
extern int npButtonState[3];
extern glm::mat4 mModelTransformMat;
extern int nLastSecond;

extern float fRotateSpeed;
extern float fTranslateSpeed;
extern float fScrollSpeed;

extern float fpBoxLimit[6];

extern int nTextureLength;
extern const char* cpTextureName;
extern int* npPicWidth, * npPicHeight;
extern unsigned char** ucppPicContent;
extern int* npTextureIndex;

extern float fppLightPosition[4];
extern float fppLightAmbient[4];
extern float fppLightDiffuse[4];
extern float fppLightSpecular[4];
extern float fpMaterialShininess[1];
extern float fpMaterialSpecular[4];
extern float fpMaterialAmbientDiffuse[4];

extern char cpModFileList[100][256];
extern int npTypeList[100];
extern char cpSndFileList[100][256];
extern int nSndFileCount;
extern ALuint upSrcList[100];
extern ALuint uCurSource;

// Declarations of functions

int ReadFiles(const char* str);

void WindowInit();
void WindowCleanUp();

void Display(GLFWwindow* w);
int UnProjectNow(double x, double y, double z, double* rx, double* ry, double* rz);

void EventInit();
void MouseMotionEvent(GLFWwindow* w, double x, double y);
void MouseWheelEvent(GLFWwindow* w, double x, double y);
void MouseDropEvent(GLFWwindow* w, int c, const char** p);

void Draw();
void DrawBox();
void DrawReadFiles(int argc, char* argv[]);
void DrawCreateTexture();
void DrawCleanUp();

void Update();

void GameInit();
void GameMove(GLFWwindow* w, double x, double y);
void GameDrag(GLFWwindow* w, int c, const char** p);
void GameSecond();
void GameCleanUp();

void ModelCleanUp();

int main(int argc, char *argv[]);

#endif
