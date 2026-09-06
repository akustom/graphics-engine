#include "engine/scene/camera.hpp"

#include <GLFW/glfw3.h>
#include "engine/window/window.hpp"

namespace engine::scene {
    void Camera::setSpeed(float speed)           {movementSpeed = speed;}
    void Camera::setMouseSensitivity(float sens) {mouseSensitivity = sens;}
    void Camera::setFieldOfView(float fov)       {fieldOfView = fov;}

    void Camera::pushViewMatrix() {
        if (!isViewDirty)
            return;
        cameraUBO.pushUniform(0, rawCamera.getViewMatrix());
        isViewDirty = false;
    }

    void Camera::pushProjectionMatrix(unsigned int win_width, unsigned int win_height) const {
        cameraUBO.pushUniform(
        sizeof(glm::mat4),
        glm::perspective(glm::radians(fieldOfView),
            static_cast<float>(win_width)/static_cast<float>(win_height),
            0.1f, 10000.0f)
            );
    }

    void Camera::use(win::Window& window) {
        int width, height;
        window.getWindowSize(&width, &height);

        pushViewMatrix();
        pushProjectionMatrix(width, height);
    }

    void Camera::processKeyboard(win::Window& window, float dt) {
        if (window.isKeyPressed(GLFW_KEY_W)) {
            rawCamera.position += rawCamera.front * movementSpeed * dt;
            isViewDirty = true;
        }
        if (window.isKeyPressed(GLFW_KEY_S)) {
            rawCamera.position -= rawCamera.front * movementSpeed * dt;
            isViewDirty = true;
        }
        if (window.isKeyPressed(GLFW_KEY_A)) {
            rawCamera.position -= rawCamera.right * movementSpeed * dt;
            isViewDirty = true;
        }
        if (window.isKeyPressed(GLFW_KEY_D)) {
            rawCamera.position += rawCamera.right * movementSpeed * dt;
            isViewDirty = true;
        }
        if (window.isKeyPressed(GLFW_KEY_SPACE)) {
            rawCamera.position += rawCamera.worldUp * movementSpeed * dt;
            isViewDirty = true;
        }
        if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
            rawCamera.position -= rawCamera.worldUp * movementSpeed * dt;
            isViewDirty = true;
        }
    }
    void Camera::processMouse(win::Window& window, bool constrain_pitch) {
        double x_offset = window.cursorContext.offsetX;
        double y_offset = window.cursorContext.offsetY;

        if (x_offset == 0 && y_offset == 0)
            return;

        isViewDirty = true;

        x_offset *= mouseSensitivity;
        y_offset *= mouseSensitivity;

        rawCamera.yaw   += static_cast<float>(x_offset);
        rawCamera.pitch += static_cast<float>(y_offset);

        if (constrain_pitch) {
            if (rawCamera.pitch > 89.0f)
                rawCamera.pitch = 89.0f;
            if (rawCamera.pitch < -89.0f)
                rawCamera.pitch = -89.0f;
        }

        rawCamera.updateCameraDirectionVariable();
    }

    void Camera::sendUpdate(win::Window& window) {
        pushViewMatrix();

        int width, height;
        window.getWindowSize(&width, &height);

        pushProjectionMatrix(width, height);
    }
}