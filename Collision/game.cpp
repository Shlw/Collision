/*************************************************************************
 * game.cpp for project Collision
 * Author : lzh
 * Modifier : Shlw lzh
 * Description : Source file to implement Game, which handles the game
 * logic, that is, to determine when to release a new object and something
 * like that.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

void GameInit()
{
    oppObjectList[nObjectTot] = new Object(1, 1, 0.0, 0.0, 0.0);
    *oppObjectList[nObjectTot]->mpFrame = glm::translate(glm::mat4(1.0), glm::vec3(0.2, 0.4, 0.0));
    *oppObjectList[nObjectTot++]->vpSpeed = glm::vec3(0.005, 0.005, 0.0);
    oppObjectList[nObjectTot] = new Object(1, 1, 0.0, 0.0, 0.0);
    *oppObjectList[nObjectTot]->mpFrame = glm::translate(glm::rotate(glm::mat4(1.0), (float)(M_PI/6.0), glm::vec3(1.0, 1.0, 1.0)), glm::vec3(0.8, 0.4, 0.0));
    *oppObjectList[nObjectTot++]->vpSpeed = glm::vec3(-0.005, 0.005, 0.0);
    oppObjectList[nObjectTot] = new Object(1, 1, 0.0, 0.0, 0.0);
    *oppObjectList[nObjectTot]->mpFrame = glm::mat4(1.0);
    *oppObjectList[nObjectTot++]->vpSpeed = glm::vec3(0.002, 0.004, 0.0);
    return ;
}

// Implementation of Game
void Game()
{
    // Counter to count the number of seconds passed
    static int nSecCtr = 0;
    
    // Judge whether to release a new object
    if (nLastClock/1000 > nSecCtr)
    {
        // Update nSecCtr
        nSecCtr = nLastClock/1000;

        // Judge whether space is available
        if (nObjectTot < 5)
        {
            // Release a new object.
            oppObjectList[nObjectTot] = new Object(2, 2, 0.0, 0.0, 0.0);
            *oppObjectList[nObjectTot]->mpFrame = glm::translate(glm::mat4(1.0), glm::vec3(0.2, 0.4, 0.0));
            *oppObjectList[nObjectTot++]->vpSpeed = glm::vec3(0.005, 0.005, 0.0);
        }
    }
    
    return ;
}
