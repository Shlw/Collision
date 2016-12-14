/*************************************************************************
 * update.cpp for project Collision
 * Author : lzh
 * Modifier : lzh
 * Description : Source file to implement functions about update and
 * collision detection.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

// Implementation of Object::Update
void Object::Update()
{
    // **ATTENTION** glm::mat4 stores in column-major, see glm Manual.
    // Check weather reached the left border
    
    if ((*mpFrame)[3][0] < fpBoxLimit[0])
        // Reverse the X-component of vSpeed
        (*vpSpeed)[0] = fabs((*vpSpeed)[0]);
    if ((*mpFrame)[3][0] > fpBoxLimit[1])
        (*vpSpeed)[0] = -fabs((*vpSpeed)[0]);
    if ((*mpFrame)[3][1] < fpBoxLimit[2])
        (*vpSpeed)[1] = fabs((*vpSpeed)[1]);
    if ((*mpFrame)[3][1] > fpBoxLimit[3])
        (*vpSpeed)[1] = -fabs((*vpSpeed)[1]);
    if ((*mpFrame)[3][2] < fpBoxLimit[4])
        (*vpSpeed)[2] = fabs((*vpSpeed)[2]);
    if ((*mpFrame)[3][2] > fpBoxLimit[5])
        (*vpSpeed)[2] = -fabs((*vpSpeed)[2]);
    
    // Move the mFrame using the global coordinates
    *mpFrame = glm::translate(glm::mat4(1.0), (*vpSpeed) * (float)(dLastClock - dLastLastClock)) * (*mpFrame);
    
    return ;
}

void Update()
{
    for (int i = 0; i < nObjectTot; i++)
        oppObjectList[i]->Update();
    return ;
}
