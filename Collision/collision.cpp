/*************************************************************************
 * main.cpp for project Collision
 * Author : lzh
 * Modifier : Shlw lzh Shlw
 * Rev : 2016.12.05.18.43
 * Description : Source file to implement main, which calls functions and
 * enters glutMainLoop.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

// The main function
int main(int argc, char *argv[])
{
    srand(time(NULL));

    ReadFiles();

    EventInit();

    GameInit();

    // Initialize function of glut
    glutInit(&argc, argv);
    glutInitDisplayMode(nWindowFlags);
    glutInitWindowSize(nInitWindowWidth, nInitWindowHeight);

    // Create a window and initialilze
    glutCreateWindow(cpWindowTitle);
    WindowInit();

    // Register display function
    glutDisplayFunc(Display);

    // Register mouse event process function
    glutMouseFunc(MouseButtonEvent);
    glutMotionFunc(MouseMotionEvent);
    glutPassiveMotionFunc(MousePassiveMoveEvent);
    glutMouseWheelFunc(MouseWheelEvent);

    // Setup a timer to refresh
    glutTimerFunc(nTimerSpeed, OnTimer, 1);

    // Go on main loop until Quit is called
    glutMainLoop();

    ModelCleanUp();

    return 0;
}
