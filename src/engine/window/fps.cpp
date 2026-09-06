#include "engine/window/fps.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>


namespace engine::win {
    void FrameTimer::setFPS(float fps) {
        static constexpr double eps = 0.0009;

        std::this_thread::sleep_for(std::chrono::duration<double>(1.0f/fps - (glfwGetTime() - fpsLastFrame) - eps));

        fpsLastFrame = glfwGetTime();
    }

    double FrameTimer::getFrameTime() {
        dtLastFrame = dtCurrentFrame;
        dtCurrentFrame = glfwGetTime();
        return dtCurrentFrame - dtLastFrame;
    }
}
