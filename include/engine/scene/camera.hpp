#pragma once

#include "engine/geometry/camera.hpp"
#include "glw/primitive/buffer.hpp"


namespace engine::win {
    struct Window;
}

namespace engine::scene {
    class Camera {
        geo::Camera rawCamera;

        float movementSpeed     = 5.0f;
        float mouseSensitivity  = 0.1f;
        float fieldOfView       = 45.0f;

        glw::UBO cameraUBO;

        bool isViewDirty = true;

        void pushViewMatrix();

        void pushProjectionMatrix(int win_width, int win_height) const;

    public:
        Camera(int binding_loc) {
            cameraUBO.bind(binding_loc);
            cameraUBO.allocateBuffer(2 * util::bytesof<glm::mat4>());
        }

        void setSpeed(float speed = 5.0f);
        void setMouseSensitivity(float sens = 0.1f);
        void setFieldOfView(float fov = 45.0f);

        void use(win::Window& window);

        void processKeyboard(win::Window& window, float dt);
        void processMouse(win::Window& window, bool constrain_pitch = true);

        void sendUpdate(win::Window& window);
    };
}
