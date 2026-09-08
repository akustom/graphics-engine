#pragma once


namespace engine::win {
    class FrameTimer {
    public:
        void   setFPS(double fps);
        double getFrameTime();
        void   setTarget(double fps);
        [[nodiscard]] double getTarget() const;

    private:
        double target_time = 0;

        double fpsLastFrame = 0;

        double dtLastFrame = 0;
        double dtCurrentFrame = 0;
    };
}
