/*************************************************************************
 * game.cpp for project Collision
 * Author : lzh
 * Modifier : Shlw lzh Shlw lzh
 * Description : Source file to implement Game, which handles the game
 * logic, that is, to determine when to release a new object and something
 * like that.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

void GameInit()
{
    oppObjectList[nObjectTot] = new Object(1, 0.0, 0.0, 0.0);
    *oppObjectList[nObjectTot]->mpFrame = glm::translate(glm::mat4(1.0), glm::vec3(0.2, 0.4, 0.0));
    *oppObjectList[nObjectTot++]->vpSpeed = glm::vec3(0.2, 0.2, 0.0);
    oppObjectList[nObjectTot] = new Object(1, 0.0, 0.0, 0.0);
    *oppObjectList[nObjectTot]->mpFrame = glm::translate(glm::rotate(glm::mat4(1.0), (float)(M_PI/6.0), glm::vec3(1.0, 1.0, 1.0)), glm::vec3(0.8, 0.4, 0.0));
    *oppObjectList[nObjectTot++]->vpSpeed = glm::vec3(-0.2, 0.2, 0.0);
    oppObjectList[nObjectTot] = new Object(1, 0.0, 0.0, 0.0);
    *oppObjectList[nObjectTot]->mpFrame = glm::mat4(1.0);
    *oppObjectList[nObjectTot++]->vpSpeed = glm::vec3(0.3, 0.6, 0.0);
    return ;
}

void GameMove(GLFWwindow* w, double x, double y)
{
    return ;
}

void GameDrag(GLFWwindow* w, int c, const char** p)
{
    double x1, x2, y1, y2, z1, z2;
    UnProjectNow(dLastMouseX, dLastMouseY, 0.6, &x1, &y1, &z1);
    UnProjectNow(dLastMouseX, dLastMouseY, 0.9, &x2, &y2, &z2);
    oppObjectList[nObjectTot] = new Object(3, 0.0, 0.0, 0.0);
    *oppObjectList[nObjectTot]->mpFrame = glm::translate(glm::mat4(1.0), glm::vec3(x1, y1, z1));
    *oppObjectList[nObjectTot++]->vpSpeed = glm::vec3(x2-x1, y2-y1, z2-z1);
    return;
}
