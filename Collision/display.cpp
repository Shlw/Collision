#include "global.hpp"

int nWindowFlags = GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE;
int nInitWindowWidth = 1024, nInitWindowHeight = 768;
const char* cpWindowTitle = "Collision Demo";

int nLastClock;

int nModelCtr;
Model mpModelList[30];
int nObjectCtr;
Object opObjectList[30];

void WindowInit(void)
{
    nModelCtr = 0;
    nObjectCtr = 0;
    mpModelList->nLength = 3;
    mpModelList->vpVertex[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    mpModelList->vpColor[0] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    mpModelList->vpVertex[1] = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);
    mpModelList->vpColor[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    mpModelList->vpVertex[2] = glm::vec4(0.5f, 0.0f, 0.0f, 1.0f);
    mpModelList->vpColor[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
    nModelCtr++;
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
    
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0d);
    
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(45.0d, double(nInitWindowWidth) / double(nInitWindowHeight), 0.1d, 10.0d);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0d, 0.0d, 4.0d, 0.0d, 0.0d, 0.0d, 0.0d, 1.0d, 0.0d);
    
    return;
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (int i = 0; i < nObjectCtr; i++)
        (opObjectList+i)->Draw();
    for (int i = 0; i < nObjectCtr; i++)
        (opObjectList+i)->Update();
    
    Game();
    
    glutSwapBuffers();
    
    Sleep(10);
    
    glutPostRedisplay();
    
    nLastClock = clock();
    
    return ;
}
