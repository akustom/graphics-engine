#include "engine/window/fps.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>

#include <immintrin.h>

namespace stc = std::chrono;

namespace engine::win {
    void FrameTimer::setFPS(float fps) {
        static double eps = 1/fps * 0.175;

        double sleep_time = 1.0f/fps - (glfwGetTime() - fpsLastFrame);
        std::this_thread::sleep_for(stc::duration<double>(sleep_time - eps));

        while (1.0f/fps >= glfwGetTime() - fpsLastFrame) {_mm_pause();}

        fpsLastFrame = glfwGetTime();
    }

    double FrameTimer::getFrameTime() {
        dtLastFrame = dtCurrentFrame;
        dtCurrentFrame = glfwGetTime();
        return dtCurrentFrame - dtLastFrame;
    }
}
