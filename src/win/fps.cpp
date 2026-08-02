#include "win/fps.hpp"

#include "GLFW/glfw3.h"


namespace win {
    void FrameTimer::setFPS(float fps) {
        while (1.0f/fps - (glfwGetTime() - fpsLastFrame) >= 0) {}

        fpsLastFrame = glfwGetTime();
    }

    double FrameTimer::getFrameTime() {
        dtLastFrame = dtCurrentFrame;
        dtCurrentFrame = glfwGetTime();
        return dtCurrentFrame - dtLastFrame;
    }
}
