#include "../../common/Time.h"

#ifndef __APPLE__

#include <GLFW/glfw3.h>

double GetTimeSeconds() {
    return glfwGetTime();
}

#endif
