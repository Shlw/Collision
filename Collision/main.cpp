#include "global.hpp"

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(nWindowFlags);
    glutInitWindowSize(nInitWindowWidth, nInitWindowHeight);
    glutCreateWindow(cpWindowTitle);
    WindowInit();
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
