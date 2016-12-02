/*************************************************************************
 * display.cpp for project Collision
 * Author : lzh
 * Rev : 2016.12.02.10.18
 * Description : Source file to handle things releated to display,
 * including the initialization of window, mouse event, and calls Game,
 * Object::Draw and Object::Update.
 * Note : This source file is a naive example and should be rewritten.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

// Declarations of global variables
int nWindowFlags = GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE;
int nInitWindowWidth = 1024, nInitWindowHeight = 768;
int nTimerSpeed = 20;
const char* cpWindowTitle = "Collision Demo";
int nLastClock;

// Declarations of Model list and Object lists
int nModelCtr;
Model mpModelList[30];
int nObjectCtr;
Object opObjectList[30];

// Initialize the windows as well as initialize some variables.
void WindowInit(void)
{
    // Initialize the counter of Model list and Object list.
    nModelCtr = 0;
    nObjectCtr = 0;
    
    // Add a new model of RGB triangle
    mpModelList->nLength = 3;
    mpModelList->vpVertex[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    mpModelList->vpColor[0] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    mpModelList->vpVertex[1] = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);
    mpModelList->vpColor[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    mpModelList->vpVertex[2] = glm::vec4(0.5f, 0.0f, 0.0f, 1.0f);
    mpModelList->vpColor[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
    nModelCtr++;
    
    // Add three objects of Model 0
    // **ATTENTION** Object 1 is created with its mFrame rotated, and
    // therefore you may observe Object 1 get through other Object, which
    // is resulted from that Object 1 is not in the same plane as other
    // Objects.
    opObjectList->mFrame = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.4f, 0.0f));
    opObjectList->vSpeed = glm::vec3(0.005f, 0.005f, 0.0f);
    opObjectList->nModelIndex = 0;
    nObjectCtr++;
    (opObjectList+1)->mFrame = glm::translate(glm::rotate(glm::mat4(1.0f), (float)M_PI/6.0f, glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(0.8f, 0.4f, 0.0f));
    (opObjectList+1)->vSpeed = glm::vec3(-0.005f, 0.005f, 0.0f);
    (opObjectList+1)->nModelIndex = 0;
    nObjectCtr++;
    (opObjectList+2)->mFrame = glm::mat4(1.0f);
    (opObjectList+2)->vSpeed = glm::vec3(0.002f, 0.004f, 0.0f);
    (opObjectList+2)->nModelIndex = 0;
    nObjectCtr++;
    
    // Enable OpenGL features
    glEnable(GL_DEPTH_TEST);
    
    // Set up the values when clearing buffers
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0d);
    
    // Set up the projection
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(45.0d, double(nInitWindowWidth) / double(nInitWindowHeight), 0.1d, 10.0d);
    
    // Set up the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0d, 0.0d, 4.0d, 0.0d, 0.0d, 0.0d, 0.0d, 1.0d, 0.0d);
    
    return;
}

// Call for display when timer is on, as well as updating some variables
void OnTimer(int nValue)
{
    // Update nLastClock to supply a stable time counter
    nLastClock = clock();
    
    // Call for display
    glutPostRedisplay();
    
    // Set up another timer
    glutTimerFunc(nTimerSpeed, OnTimer, 1);
    
    return ;
}
void Display(void)
{
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw each Object
    for (int i = 0; i < nObjectCtr; i++)
        (opObjectList+i)->Draw();
    
    // Update each Object
    for (int i = 0; i < nObjectCtr; i++)
        (opObjectList+i)->Update();
    
    // Handle game logic
    Game();
    
    // Swap buffers to refresh
    glutSwapBuffers();
    
    return ;
}
