/*************************************************************************
 * draw.cpp for project Collision
 * Author : lzh
 * Modifier : lzh
 * Rev : 2016.12.01.22.13
 * Description : Source file to implement Object::Draw, which draws
 * objects in different coordinates of Object.
 * Note : This source file is a naive example and should be rewritten.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

// Implementation of Object::Draw
void Object::Draw(void)
{
    // Switch to ModelView Matrix
    glMatrixMode(GL_MODELVIEW);
    
    // Save current matrix
    glPushMatrix();
    
    // Multiply mFrame to the right of current matrix in order to
    // transform coordinates in each Object to the global coordinates of
    // OpenGL.
    glMultMatrixf(glm::value_ptr(mFrame));
    
    // Draw triangles
    glBegin(GL_TRIANGLES);
        for (int i = 0; i < (mpModelList+nModelIndex)->nLength; i++)
        {
            glVertex4fv(glm::value_ptr((mpModelList+nModelIndex)->vpVertex[i]));
            glColor4fv(glm::value_ptr((mpModelList+nModelIndex)->vpColor[i]));
        }
    glEnd();
    
    // Restore matrix
    glPopMatrix();
    
    return ;
}
