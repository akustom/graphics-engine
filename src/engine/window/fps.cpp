#include "engine/window/fps.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#include <immintrin.h>

#include <tracy/Tracy.hpp>


namespace std_c = std::chrono;

namespace engine::win {
    void FrameTimer::setFPS(double fps) {
        ZoneScoped;
        double eps = target_time * 0.175;

        double sleep_time = target_time - (glfwGetTime() - fpsLastFrame);

        std::this_thread::sleep_for(std_c::duration<double>(sleep_time - eps));

        while (target_time >= glfwGetTime() - fpsLastFrame) {
            _mm_pause();
        }

        fpsLastFrame = glfwGetTime();
    }

    double FrameTimer::getFrameTime() {
        dtLastFrame = dtCurrentFrame;
        dtCurrentFrame = glfwGetTime();
        return dtCurrentFrame - dtLastFrame;
    }

    void FrameTimer::setTarget(double fps) {
        target_time = 1.0/fps;
    }

    double FrameTimer::getTarget() const {
        return 1/target_time;
    }
}
