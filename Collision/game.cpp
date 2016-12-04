/*************************************************************************
 * game.cpp for project Collision
 * Author : lzh
 * Modifier : Shlw
 * Rev : 2016.12.04.23.40
 * Description : Source file to implement Game, which handles the game
 * logic, that is, to determine when to release a new object and something
 * like that.
 * Note : This source file is a naive example and should be rewritten.
 * Note_Shlw : This file should consider the different time setting in MacOS Linux & windows,
 			   since it can not work properly on my Ubuntu QAQ
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

// Implementation of Game
void Game(void)
{
    // Counter to count the number of seconds passed
    static int nSecCtr = 0;

    // Judge whether to release a new object
    if (nLastClock*10/CLOCKS_PER_SEC > nSecCtr)
    {
        // Update nSecCtr
        nSecCtr = clock()*10/CLOCKS_PER_SEC;

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
