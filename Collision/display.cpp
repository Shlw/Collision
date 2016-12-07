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
    
    // Set up the values when clearing buffers
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    
    // Set up blend function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Set up smooth hints
    glHint(GL_POINT_SMOOTH, GL_NICEST);
    glHint(GL_LINE_SMOOTH, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH, GL_NICEST);

    // Set up the projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, double(nInitWindowWidth) / double(nInitWindowHeight), 0.1, 10.0);

    // Set up the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    return;
}

// Call for display when timer is on, as well as updating some variables
void OnTimer(int nValue)
{
    // Update nLastClock to supply a stable time counter
    nLastClock = clock();

    // Call for display
    glutPostRedisplay();

    // Set up another timer
    glutTimerFunc(nTimerSpeed, OnTimer, 1);

    return ;
}
void Display()
{
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw each Object
    Draw();

    // Update each Object
    Update();
    
    // Handle game logic
    Game();

    // Swap buffers to refresh
    glutSwapBuffers();

    return ;
}
