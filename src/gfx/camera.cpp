#include "gfx/camera.hpp"

#include <cmath>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glw/buffer.hpp"


namespace gfx {
    glm::mat4 Camera::getViewMatrix() const {return glm::lookAt(position, position + front, up);}
    void Camera::updateSpeed(float speed)           {movementSpeed = speed;}
    void Camera::updateMouseSensitivity(float sens) {mouseSensitivity = sens;}
    void Camera::updateFieldOfView(float fov)       {fieldOfView = fov;}

    void Camera::updateCameraDirectionVariable() {
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);
        right = glm::normalize(glm::cross(newFront, worldUp));
        up    = glm::normalize(glm::cross(right, newFront));
    }
}
