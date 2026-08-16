#pragma once


namespace engine::win {
    struct FrameTimer {
        double fpsLastFrame = 0;

        void setFPS(float fps);

        double dtLastFrame = 0;
        double dtCurrentFrame = 0;

        double getFrameTime();
    };
}
