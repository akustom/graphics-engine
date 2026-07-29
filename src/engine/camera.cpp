#include "engine/camera.hpp"

#include "win/window.hpp"

namespace engine {
    void Camera::pushViewMatrix() {
        if (!rawCamera.isViewDirty)
            return;
        cameraUBO.pushUniform(0, rawCamera.getViewMatrix());
        rawCamera.isViewDirty = false;
    }

    void Camera::pushProjectionMatrix(int win_width, int win_height) const {
        cameraUBO.pushUniform(
        bytesof<glm::mat4>(),
        glm::perspective(glm::radians(rawCamera.fieldOfView),
            static_cast<float>(win_width)/static_cast<float>(win_height),
            0.1f, 1732.0f)
            );
    }

    void Camera::use(const win::Window& window) {
        window.setUserPointer(&rawCamera);

        int width, height;
        window.getWindowSize(&width, &height);

        pushViewMatrix();
        pushProjectionMatrix(width, height);
    }

    void Camera::processKeyboard(const win::Window& window, float dt) {
        rawCamera.processKeyboard(window, dt);
    }
    void Camera::processMouse(double x_offset, double y_offset, bool constrain_pitch){
        rawCamera.processMouse(x_offset, y_offset, constrain_pitch);
    }

    void Camera::sendUpdate() {
        pushViewMatrix();
    }
}