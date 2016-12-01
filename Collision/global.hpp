/*************************************************************************
 * global.hpp for project Collision
 * Author : lzh
 * Rev : 2016.12.01.14.44
 * Description : Global header for the whole project, including
 * inclusion of public headers and declarations.
 ************************************************************************/

// Check whether included

#ifndef CL_GLOBAL_HPP

#define CL_GLOBAL_HPP

// Include public headers

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

// Class declarations of Model and Object
// **ATTENTION** Public here is convenient but ugly, these classes are
// suggested to be overridden.
// **ATTENTION** Here used glm::vec* and glm::mat* to represent vectors
// and matrices, but frequent construction and destruction which is
// automatically called by the classes may result in low efficiency. Using
// pointers to create instance of these object may be better.

// The class to store models which can be used repeatedly, only storing
// vertices coordinates and colors. The vertices coordinates will be drawn
// with respect to the coordinates of each Object individually.
class Model
{
public:
    int nLength;
    glm::vec4 vpVertex[30];
    glm::vec4 vpColor[30];
};

// The class to store objects, only storing the index of model in the
// mpModelList and the center, the vector of x, y, z-axes and the speed.
// To be exactly, the entries [0][0:2], [1][0:2], [2][0:2] represent the
// vector of x, y, z-axes respectively, and [3][0:2] represent the center
// of the Object, where [i][j] represent the ith row and jth column of the
// matrix and all the coordinates are that in OpenGL global coordinates.
// Each Object use mFrame to establish a new coordinates, and the Model is
// drawn with respect to the new coordinates. Note that the entry [0:2][3]
// must be 0 and the entry [3][3] 1.
// **ATTENTION** glm::mat4 stores in column-major, see glm Manual.
class Object
{
public:
    glm::mat4 mFrame;
    glm::vec3 vSpeed;
    int nModelIndex;
    
    void Draw(void);
    void Update(void);
};

// Declarations of global variables defined in .cpp files

extern int nWindowFlags;
extern int nInitWindowWidth, nInitWindowHeight;
extern int nTimerSpeed;
extern const char* cpWindowTitle;
extern int nLastClock;

// Declarations of Model list and Object lists

extern int nModelCtr;
extern Model mpModelList[30];
extern int nObjectCtr;
extern Object opObjectList[30];

// Declarations of functions

void WindowInit(void);

void OnTimer(int nValue);
void Display(void);

void Game(void);

int main(int argc, char *argv[]);

#endif
