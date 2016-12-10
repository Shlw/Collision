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
    GLFWwindow* fwWindow;

    srand(time(NULL));

    ReadFiles();

    EventInit();

    GameInit();
    
    if (!glfwInit())
        return -1;
    
    // Initialize function of glut
    
    fwWindow = glfwCreateWindow(nInitWindowWidth, nInitWindowHeight, cpWindowTitle, NULL, NULL);
    
    if (!fwWindow)
    {
        glfwTerminate();
        return -1;
    }
    
    // Create a window and initialilze
    glfwMakeContextCurrent(fwWindow);
    WindowInit();
    
    while (!glfwWindowShouldClose(fwWindow))
    {
        // Display here
        Display(fwWindow);
        
        // Poll for and process events
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    ModelCleanUp();

    return 0;
}
