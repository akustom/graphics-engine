#include "engine/window/fps.hpp"

#include <GLFW/glfw3.h>


namespace engine::win {
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
