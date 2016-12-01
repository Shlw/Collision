#include "global.hpp"

void Object::Draw(void)
{
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(mFrame));
    glBegin(GL_TRIANGLES);
        for (int i = 0; i < (mpModelList+nModelIndex)->nLength; i++)
        {
            glVertex4fv(glm::value_ptr((mpModelList+nModelIndex)->vpVertex[i]));
            glColor4fv(glm::value_ptr((mpModelList+nModelIndex)->vpColor[i]));
        }
    glEnd();
    glPopMatrix();
    return ;
}
