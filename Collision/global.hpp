#ifndef CL_GLOBAL_HPP

#define CL_GLOBAL_HPP

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Model
{
public:
    int nLength;
    glm::vec4 vpVertex[30];
    glm::vec4 vpColor[30];
};

class Object
{
public:
    glm::mat4 mFrame;
    glm::vec3 vSpeed;
    int nModelIndex;
    
    void Draw(void);
    void Update(void);
};

extern int nWindowFlags;
extern int nInitWindowWidth, nInitWindowHeight;
extern const char* cpWindowTitle;

extern int nModelCtr;
extern Model mpModelList[30];
extern int nObjectCtr;
extern Object opObjectList[30];

extern int nLastClock;

void WindowInit(void);

void Display(void);

void Game(void);

int main(int argc, char *argv[]);

#endif
