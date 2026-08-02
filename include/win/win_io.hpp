#pragma once


struct GLFWwindow;

namespace io {
    void cursor_pos_callback(GLFWwindow* window, const double x_pos, const double y_pos);

    void mouse_button_callback(GLFWwindow* window, const int button, const int action, const int mods);
}