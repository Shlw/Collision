/*************************************************************************
 * main.cpp for project Collision
 * Author : lzh
 * Modifier : Shlw
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

    // Setup a timer to refresh
    glutTimerFunc(nTimerSpeed, OnTimer, 1);

    // Go on main loop until Quit is called
    glutMainLoop();
    
    CleanUp();
    
    return 0;
}