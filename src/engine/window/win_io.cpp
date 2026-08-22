#include "engine/window/win_io.hpp"

#include <GLFW/glfw3.h>
#include "engine/window/window.hpp"


namespace engine::win {
    void cursor_pos_callback(GLFWwindow* window, const double x_pos, const double y_pos) {
        if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
            return;

        auto* currentWindow = static_cast<win::Window*>(glfwGetWindowUserPointer(window));

        if (!currentWindow->cursorContext.initialized) {
            currentWindow->cursorContext.initialized = true;
            currentWindow->cursorContext.lastX = static_cast<float>(x_pos);
            currentWindow->cursorContext.lastY = static_cast<float>(y_pos);
        }
        currentWindow->cursorContext.offsetX = static_cast<float>(x_pos - currentWindow->cursorContext.lastX);
        currentWindow->cursorContext.offsetY = static_cast<float>(currentWindow->cursorContext.lastY - y_pos);

        currentWindow->cursorContext.lastX = static_cast<float>(x_pos);
        currentWindow->cursorContext.lastY = static_cast<float>(y_pos);
    }

    void mouse_button_callback(GLFWwindow* window, const int button, const int action, const int mods) {
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            auto* currentWindow = static_cast<win::Window*>(glfwGetWindowUserPointer(window));
            if (action == GLFW_PRESS) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                currentWindow->cursorContext.initialized = false;
            }
            else if (action == GLFW_RELEASE) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
    }
}