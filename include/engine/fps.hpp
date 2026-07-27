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

        static void setFPS(float fps) {
            static double lastFrame = 0;

            while (1.0f/fps - (glfwGetTime() - lastFrame) >= 0) {}

            lastFrame = glfwGetTime();
        }
    };
}
