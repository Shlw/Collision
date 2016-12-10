/*************************************************************************
 * display.cpp for project Collision
 * Author : lzh
 * Modifier : lzh
 * Description : Source file to handle things releated to display,
 * including the initialization of window, mouse event, and calls other
 * functional parts.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

// Initialize the windows as well as initialize some variables.
void WindowInit()
{
    
    // Enable OpenGL features
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_MULTISAMPLE);
    
    // Set up the values when clearing buffers
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    
    // Set up blend function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    
    // Set up the projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, double(nInitWindowWidth) / double(nInitWindowHeight), 0.1, 40.0);
    
    // Set up the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    
    glPointSize(2.0);
    glLineWidth(1.5);
    
    glfwSwapInterval(1);
    
    return;
}

void Display(GLFWwindow* w)
{
    nLastLastClock = nLastClock;
    nLastClock = glfwGetTime();
    
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw each Object
    Draw();
    
    // Update each Object
    Update();
    
    // Handle game logic
    Game();
    
    // Swap buffers to refresh
    glfwSwapBuffers(w);
    
    return ;
}

void WindowCleanUp()
{
    glPopMatrix();
    return ;
}
