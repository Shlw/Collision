/*************************************************************************
 * update.cpp for project Collision
 * Author : lzh
 * Rev : 2016.12.02.14.53
 * Description : Source file to implement Object::Update, which updates
 * mFrame of each Object in order to achieve movement of Objects and
 * collision detection.
 * Note : This source file is a naive example and should be rewritten.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

// Implementation of Object::Update
void Object::Update(void)
{
    // **ATTENTION** glm::mat4 stores in column-major, see glm Manual.
    
    // Check weather reached the left border
    if (glm::value_ptr(mFrame)[12] < -1.0)
        // Reverse the X-component of vSpeed
        glm::value_ptr(vSpeed)[0] = fabs(glm::value_ptr(vSpeed)[0]);
    if (glm::value_ptr(mFrame)[12] > 1.0)
        glm::value_ptr(vSpeed)[0] = -fabs(glm::value_ptr(vSpeed)[0]);
    if (glm::value_ptr(mFrame)[13] < -1.0)
        glm::value_ptr(vSpeed)[1] = fabs(glm::value_ptr(vSpeed)[1]);
    if (glm::value_ptr(mFrame)[13] > 1.0)
        glm::value_ptr(vSpeed)[1] = -fabs(glm::value_ptr(vSpeed)[1]);
    
    // Move the mFrame
    mFrame = glm::translate(mFrame, vSpeed);
    
    return ;
}
