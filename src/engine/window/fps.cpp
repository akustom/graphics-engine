#include "engine/window/fps.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#include <windows.h>
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")


namespace engine::win {
    void FrameTimer::setFPS(float fps) {
        static constexpr double eps = 0.0009;

        timeBeginPeriod(1);
            std::this_thread::sleep_for(std::chrono::duration<double>(1.0f/fps - (glfwGetTime() - fpsLastFrame) - eps));
        timeEndPeriod(1);

        fpsLastFrame = glfwGetTime();
    }

    double FrameTimer::getFrameTime() {
        dtLastFrame = dtCurrentFrame;
        dtCurrentFrame = glfwGetTime();
        return dtCurrentFrame - dtLastFrame;
    }
}
