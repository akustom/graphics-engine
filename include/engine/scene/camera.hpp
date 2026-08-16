#pragma once

#include "engine/geometry/camera.hpp"
#include "glw/buffer.hpp"


namespace engine::win {
    struct Window;
}

namespace engine::scene {
    class Camera {
        geo::Camera rawCamera;
        glw::UBO cameraUBO;

        bool isViewDirty = true;

        void pushViewMatrix();

        void pushProjectionMatrix(int win_width, int win_height) const;

    public:
        Camera(int binding_loc) {
            cameraUBO.bind(binding_loc);
            cameraUBO.allocateBuffer(2 * util::bytesof<glm::mat4>());
        }

        void use(win::Window& window);

        void processKeyboard(win::Window& window, float dt);
        void processMouse(win::Window& window, bool constrain_pitch = true);

        void sendUpdate(win::Window& window);
    };
}
