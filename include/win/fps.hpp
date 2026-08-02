#pragma once

#include <thread>
#include <chrono>

#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace win {
    struct FrameTimer {
        double dtLastFrame = 0;
        double dtCurrentFrame = 0;

        double getFrameTime() {
            dtLastFrame = dtCurrentFrame;
            dtCurrentFrame = glfwGetTime();
            return dtCurrentFrame - dtLastFrame;
        }

        double fpsLastFrame = 0;

        void setFPS(float fps) {
            while (1.0f/fps - (glfwGetTime() - fpsLastFrame) >= 0) {}

            fpsLastFrame = glfwGetTime();
        }
    };
}
