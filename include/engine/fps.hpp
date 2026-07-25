#pragma once

#include <thread>
#include <chrono>

#include "GLFW/glfw3.h"


namespace engine {
    struct FrameTimer {
        static float getFrameTime() {
            static float lastFrame = 0;
            static float currentFrame = 0;

            lastFrame = currentFrame;
            currentFrame = glfwGetTime();
            return currentFrame - lastFrame;
        }

        static bool setFPS(float fps) {
            static float lastFrame = 0;

            if (1.0f/fps - (glfwGetTime() - lastFrame) >= 0)
                return true;

            lastFrame = glfwGetTime();
            return false;
        }
    };
}
