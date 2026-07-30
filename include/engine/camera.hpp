#pragma once

#include "win/window.hpp"

#include "gfx/camera.hpp"
#include "glw/buffer.hpp"


namespace engine {
    class Camera {
        gfx::Camera rawCamera;
        glw::UBO cameraUBO;

        void pushViewMatrix();

        void pushProjectionMatrix(int win_width, int win_height) const;

    public:
        Camera(int binding_point) {
            cameraUBO.bind(binding_point);
            cameraUBO.allocateBuffer(2 * bytesof<glm::mat4>());
        }

        void use(const win::Window& window);

        void processKeyboard(const win::Window& window, float dt);
        void processMouse(const win::Window& window, bool constrain_pitch = true);

        void sendUpdate();
    };
}
