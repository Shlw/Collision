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
    if ((*mpFrame)[3][0] < -1.0)
        // Reverse the X-component of vSpeed
        (*vpSpeed)[0] = fabs((*vpSpeed)[0]);
    if ((*mpFrame)[3][0] > 1.0)
        (*vpSpeed)[0] = -fabs((*vpSpeed)[0]);
    if ((*mpFrame)[3][1] < -1.0)
        (*vpSpeed)[1] = fabs((*vpSpeed)[1]);
    if ((*mpFrame)[3][1] > 1.0)
        (*vpSpeed)[1] = -fabs((*vpSpeed)[1]);

    // Move the mFrame
    *mpFrame = glm::translate(*mpFrame, glm::mat3(nLastClock - nLastLastClock)**vpSpeed);

    return ;
}

void Update()
{
    for (int i = 0; i < nObjectTot; i++)
        oppObjectList[i]->Update();
    return ;
}
