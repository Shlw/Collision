#include "global.hpp"

void Object::Update(void)
{
    if (glm::value_ptr(mFrame)[12] < -1.0f)
        glm::value_ptr(vSpeed)[0] = fabs(glm::value_ptr(vSpeed)[0]);
    if (glm::value_ptr(mFrame)[12] > 1.0f)
        glm::value_ptr(vSpeed)[0] = -fabs(glm::value_ptr(vSpeed)[0]);
    if (glm::value_ptr(mFrame)[13] < -1.0f)
        glm::value_ptr(vSpeed)[1] = fabs(glm::value_ptr(vSpeed)[1]);
    if (glm::value_ptr(mFrame)[13] > 1.0f)
        glm::value_ptr(vSpeed)[1] = -fabs(glm::value_ptr(vSpeed)[1]);
    mFrame = glm::translate(mFrame, vSpeed);
    return ;
}
