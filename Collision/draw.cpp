/*************************************************************************
 * draw.cpp for project Collision
 * Author : lzh
 * Modifier : lzh Shlw
 * Description : Source file to implement Object::Draw, which draws
 * objects in different coordinates of Object.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

void Point::DrawVertex()
{
    glVertex4fv(glm::value_ptr(*vpCoordinate));
    glColor4fv(glm::value_ptr(*vpColor));
    return ;
}

void Triangle::Draw()
{
    glBegin(GL_TRIANGLES);
        pppVertex[0]->DrawVertex();
        pppVertex[1]->DrawVertex();
        pppVertex[2]->DrawVertex();
    glEnd();
    return ;
}

void Model::Draw()
{
    for (int i = 0; i < nLength; i++)
        tppCone[i]->Draw();
    return ;
}

// Implementation of Object::Draw
void Object::Draw()
{
    // Switch to ModelView Matrix
    glMatrixMode(GL_MODELVIEW);

    // Save current matrix
    glPushMatrix();

    // Multiply mFrame to the right of current matrix in order to
    // transform coordinates in each Object to the global coordinates of
    // OpenGL.
    glMultMatrixf(glm::value_ptr(*mpFrame));

    // Draw Model
    mppModelList[nModelType]->Draw();

    // Restore matrix
    glPopMatrix();

    return ;
}

void Draw()
{
    for (int i = 0; i < nObjectTot; i++)
        oppObjectList[i]->Draw();
    return ;
}
