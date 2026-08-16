#pragma once


struct GLFWwindow;

namespace engine::win {
    void cursor_pos_callback(GLFWwindow* window, const double x_pos, const double y_pos);

    void mouse_button_callback(GLFWwindow* window, const int button, const int action, const int mods);
}