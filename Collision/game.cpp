/*************************************************************************
 * game.cpp for project Collision
 * Author : lzh
 * Rev : 2016.12.02.14.53
 * Description : Source file to implement Game, which handles the game
 * logic, that is, to determine when to release a new object and something
 * like that.
 * Note : This source file is a naive example and should be rewritten.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

// Implementation of Game
void Game(void)
{
    // Counter to count the number of seconds passed
    static int nSecCtr = 0;
    
    // Judge weather to release a new object
    if (nLastClock/CLOCKS_PER_SEC > nSecCtr)
    {
        // Update nSecCtr
        nSecCtr = clock()/1000;
        
        // Judge whether space is available
        if (nObjectCtr < 30)
        {
            // Release a new object.
            (opObjectList+nObjectCtr)->mFrame = glm::mat4(1.0);
            (opObjectList+nObjectCtr)->vSpeed = glm::vec3(0.002, 0.004, 0.0);
            (opObjectList+nObjectCtr)->nModelIndex = 0;
            nObjectCtr++;
        }
    }
    
    return ;
}
