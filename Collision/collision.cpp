/*************************************************************************
 * main.cpp for project Collision
 * Author : lzh
 * Modifier : Shlw lzh Shlw lzh lziad
 * Description : Source file to implement main, which calls functions and
 * enters glutMainLoop.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

// The main function
int main(int argc, char *argv[])
{
    int nExitCode = 0;
    try {
        GLFWwindow* fwWindow;

        srand(time(NULL));

        DrawReadFiles(argc, argv);
        
        if (!glfwInit())
            return -1;

        if (!alutInit(&argc, argv)) {
            ALenum error = alutGetError();
            fprintf(stderr, "Error when initializing openAL: %s\n",
                    alutGetErrorString(error));
            glfwTerminate();
            return -1;
        }

        EventInit();

        GameInit();

        glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
        glfwWindowHint(GLFW_SAMPLES, 8);
        glfwWindowHint(GLFW_RESIZABLE, 0);
        
        fwWindow = glfwCreateWindow(nInitWindowWidth, nInitWindowHeight, cpWindowTitle, NULL, NULL);

        if (!fwWindow)
        {
            GameCleanUp();
            alutExit();
            glfwTerminate();
            return -1;
        }

        // Create a window and initialilze
        glfwMakeContextCurrent(fwWindow);

        WindowInit();

        DrawCreateTexture();

        glfwSetCursorPosCallback(fwWindow, MouseMotionEvent);
        glfwSetScrollCallback(fwWindow, MouseWheelEvent);
        glfwSetDropCallback(fwWindow, MouseDropEvent);
        glfwSetKeyCallback(fwWindow, KeyEvent);

        while (!glfwWindowShouldClose(fwWindow))
        {
            // Display here
            Display(fwWindow);

            // Poll for and process events
            glfwPollEvents();
        }
    } catch (int e) {
        switch (e) {
            case ERROR_UNKNOWN_MODEL:
                fprintf(stderr, "Error: Unknown model!\n");
                break;
            case FILE_NOT_FOUND:
                fprintf(stderr, "Error: The file to load is not found!\n");
                break;
            case ERROR_TOO_MANY_OBJ:
                fprintf(stderr, "Error: Too many objects to load!\n");
                break;
            case ERROR_UNKNOWN_SOUND:
                fprintf(stderr, "Error: Unknown sound!\n");
                break;
            case ERROR_OPENAL:
                // Before throw this exception, do as the following:
                /// ALenum error = alGetError();
                /// fprintf(stderr, "[foo]: %s\n", alGetString(error));
                // and openAL will print a detailed error message.
                fprintf(stderr, "Error: OpenAL error, see above for details!\n");
                break;
            default:
                fprintf(stderr, "Error: Unknown error!\n");
        }
        nExitCode = e;
    }
    WindowCleanUp();
    
    GameCleanUp();
    
    ModelCleanUp();
    
    alutExit();
    
    glfwTerminate();
    
    DrawCleanUp();
    
    return nExitCode;
}
