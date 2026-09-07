#pragma once


namespace engine::win {
    class FrameTimer {
    public:
        void setFPS(float fps);
        double getFrameTime();

    private:
        double fpsLastFrame = 0;

        double dtLastFrame = 0;
        double dtCurrentFrame = 0;


    };
}
