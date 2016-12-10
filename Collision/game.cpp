/*************************************************************************
 * game.cpp for project Collision
 * Author : lzh
 * Modifier : Shlw lzh Shlw lzh lziad
 * Description : Source file to implement Game, which handles the game
 * logic, that is, to determine when to release a new object and something
 * like that.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

// path and type of the files which are already loaded
char cpFileList[100][256];
int  npTypeList[100];
// stack of past mouse positions
double dpPos[10][2];
// pointer of the stack
int    nPtr;

void GameInit()
{
    memset(cpFileList, 0, sizeof(cpFileList));
    memset(npTypeList, 0, sizeof(npTypeList));
    nPtr = 0;
    /*
     oppObjectList[nObjectTot] = new Object(1, 0.0, 0.0, 0.0);
     *oppObjectList[nObjectTot]->mpFrame = glm::translate(glm::mat4(1.0), glm::vec3(0.2, 0.4, 0.0));
     *oppObjectList[nObjectTot++]->vpSpeed = glm::vec3(0.2, 0.2, 0.0);
     oppObjectList[nObjectTot] = new Object(1, 0.0, 0.0, 0.0);
     *oppObjectList[nObjectTot]->mpFrame = glm::translate(glm::rotate(glm::mat4(1.0), (float)(M_PI/6.0), glm::vec3(1.0, 1.0, 1.0)), glm::vec3(0.8, 0.4, 0.0));
     *oppObjectList[nObjectTot++]->vpSpeed = glm::vec3(-0.2, 0.2, 0.0);
     oppObjectList[nObjectTot] = new Object(1, 0.0, 0.0, 0.0);
     *oppObjectList[nObjectTot]->mpFrame = glm::mat4(1.0);
     *oppObjectList[nObjectTot++]->vpSpeed = glm::vec3(0.3, 0.6, 0.0);
     */
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
    //UnProjectNow(dLastMouseX, dLastMouseY, 0.6, &x1, &y1, &z1);
    //UnProjectNow(dLastMouseX, dLastMouseY, 0.9, &x2, &y2, &z2);
    nPrv = nPtr - 1;
    if (nPrv < 0)
        nPrv = nPrv % 10 + 10;
    UnProjectNow(dpPos[nPtr][0], dpPos[nPtr][1], 0.6, &x2, &y2, &z2);
    UnProjectNow(dpPos[nPrv][0], dpPos[nPrv][1], 0.9, &x1, &y1, &z1);
    //printf("(%f,%f,%f)-(%f,%f,%f)\n",x1,y1,z1,x2,y2,z2);
    
    for (i = 0; i < 100 && !bFound && strlen(cpFileList[i]) > 0; ++i)
        // only consider the first file
        if (strcmp(cpFileList[i], p[0]) == 0)
            bFound = true;
    if (bFound) {
        // the model has been already loaded
        nType = npTypeList[i-1];
    } else if (i == 100) {
        // no vacant seats for the new object
        throw ERROR_TOO_MANY_OBJ;
    } else {
        // add the path first
        memcpy(cpFileList[i], p[0], strlen(p[0]) * sizeof(char));
        nType = npTypeList[i] = ReadFiles(p[0]);
    }
    oppObjectList[nObjectTot] = new Object(nType, 0.0, 0.0, 0.0);
    *oppObjectList[nObjectTot]->mpFrame = glm::translate(glm::mat4(1.0), glm::vec3(x2, y2, z2));
    glm::vec3 vel((x2-x1)*1, (y2-y1)*1, (z2-z1)*1);
    *oppObjectList[nObjectTot++]->vpSpeed = vel;
    return;
}
