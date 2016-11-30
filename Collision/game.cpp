#include "global.hpp"

void Game(void)
{
    static int nSecCtr = 0;
    if (clock()/1000 > nSecCtr)
    {
        nSecCtr = clock()/1000;
        if (nObjectCtr < 30)
        {
            (opObjectList+nObjectCtr)->mFrame = glm::mat4(1.0f);
            (opObjectList+nObjectCtr)->vSpeed = glm::vec3(0.002f, 0.004f, 0.0f);
            (opObjectList+nObjectCtr)->nModelIndex = 0;
            nObjectCtr++;
        }
    }
    return ;
}
