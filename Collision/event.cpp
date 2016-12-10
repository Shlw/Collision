/*************************************************************************
 * event.cpp for project Collision
 * Author : lzh
 * Modifier : lzh
 * Description : Source file including functions to process mouse events
 * and keyboard events.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

void EventInit()
{
    for (int i = 0; i < 3; i++)
        npButtonState[i] = 0;
    mModelTransformMat = glm::mat4(1.0);
    nLastMouseX = INT_MAX;
    nLastMouseY = INT_MAX;
    return ;
}

void MouseButtonEvent(int b, int s, int x, int y)
{/*
    int m = 0;
    switch (b)
    {
        case GLUT_LEFT_BUTTON :
            m = 0; break;
        case GLUT_MIDDLE_BUTTON :
            m = 1; break;
        case GLUT_RIGHT_BUTTON :
            m = 2; break;
    }
    if (s == GLUT_DOWN)
        npButtonState[m] = 1;
    else if (s == GLUT_UP)
        npButtonState[m] = 0;
    return ;*/
}

void MouseMotionEvent(int x, int y)
{/*
    float d = sqrt(
        (float)((x-nLastMouseX) * (x-nLastMouseX))
        +(float)((y-nLastMouseY) * (y-nLastMouseY))
    ), theta;
    if (nLastMouseX == INT_MAX || nLastMouseY == INT_MAX)
        ;
    else if (nLastMouseX == x && nLastMouseY == y)
        ;
    else if (npButtonState[0] && !npButtonState[1] && !npButtonState[2])
    {
        mModelTransformMat = glm::rotate(glm::mat4(1.0), d*fRotateSpeed ,
            glm::vec3(
                ((float)(y-nLastMouseY)) / d,
                ((float)(x-nLastMouseX)) / d,
                0.0
            )
        ) * mModelTransformMat;
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(mModelTransformMat));
    }
    else if (!npButtonState[0] && !npButtonState[1] && npButtonState[2])
    {
        mModelTransformMat = glm::translate(glm::mat4(1.0),
            glm::vec3(
                ((float)(x-nLastMouseX)) * fTranslateSpeed,
                -((float)(y-nLastMouseY)) * fTranslateSpeed,
                0.0
            )
        ) * mModelTransformMat;
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(mModelTransformMat));
    }
    else if (!npButtonState[0] && npButtonState[1] && !npButtonState[2])
    {
        theta = atan2(
            (float)x - 
            ((float)(glutGet(GLUT_WINDOW_WIDTH)/2) + 0.5),
            ((float)(glutGet(GLUT_WINDOW_HEIGHT)/2) + 0.5) 
            - (float)y
        );
        theta -= atan2(
            (float)nLastMouseX - 
            ((float)(glutGet(GLUT_WINDOW_WIDTH)/2) + 0.5),
            ((float)(glutGet(GLUT_WINDOW_HEIGHT)/2) + 0.5) 
            - (float)nLastMouseY
        );
        mModelTransformMat = glm::rotate(glm::mat4(1.0),
            -theta,
            glm::vec3(0.0, 0.0, 1.0)
        ) * mModelTransformMat;
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(mModelTransformMat));
    }
    nLastMouseX = x;
    nLastMouseY = y;
    return ;*/
}

void MousePassiveMoveEvent(int x, int y)
{/*
    nLastMouseX = x;
    nLastMouseY = y;
    return ;*/
}

void MouseWheelEvent(int b, int d, int x, int y)
{/*
    mModelTransformMat = glm::translate(glm::mat4(1.0),
        glm::vec3(0.0, 0.0, (float)d*fScrollSpeed)
    ) * mModelTransformMat;
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(mModelTransformMat));
    nLastMouseX = x;
    nLastMouseY = y;
    return ;*/
}
