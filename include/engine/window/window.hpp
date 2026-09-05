#pragma once

#include "fps.hpp"
#include "cursor_ctx.hpp"


struct GLFWwindow;

namespace engine::win {
    struct Window {
        GLFWwindow* glfw_window = nullptr;

        FrameTimer frameTimer;
        CursorContext cursorContext;

        float winFPS = 60;

        static void setHints(int major_version, int minor_version);
        void init(int width, int height, const char* window_name);
        void destroy() const;

        Window() = default;
        Window(unsigned int width, unsigned int height, const char* window_name) {
            init(width, height, window_name);
        }
        ~Window() {
            destroy();
        }
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        Window(Window&& other) noexcept {
            glfw_window = other.glfw_window;
            other.glfw_window = nullptr;

            frameTimer = other.frameTimer;
            other.frameTimer = {};

            cursorContext = other.cursorContext;
            other.cursorContext = {};

            winFPS = other.winFPS;
            other.winFPS = 60;
        }
        Window& operator=(Window&& other) noexcept {
            if (this == &other)
                return *this;
            if (glfw_window)
                destroy();

            glfw_window = other.glfw_window;
            other.glfw_window = nullptr;

            frameTimer = other.frameTimer;
            other.frameTimer = {};

            cursorContext = other.cursorContext;
            other.cursorContext = {};

            return *this;
        }

        void use() const;
        void setVSync(bool enabled);

        void setInputMode(int mode, int value) const;
        void setSetFramebufferSizeCallback() const;
        void setCursorPosCallback(void(*cursor_callback)(GLFWwindow* window, double x_pos, double y_pos)) const;
        void setMouseButtonCallback(void(*mouse_button_callback)(GLFWwindow* window, int button, int action, int mods)) const;
        void setUserPointer(void* user_pointer) const;

        [[nodiscard]] bool isKeyPressed(int key) const;

        void getWindowSize(int* width, int* height) const;

        void setFPS(float fps);
        double getFrameTime();

        void startFrame(float r, float g, float b, float a);
        void endFrame();
    };
}
