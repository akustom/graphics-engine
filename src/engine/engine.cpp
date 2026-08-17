#include "engine/engine.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace engine {
    void Engine::Init() {
        glfwInit();

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        GLFWwindow* dummy = glfwCreateWindow(1, 1, "dummy", nullptr, nullptr);
        glfwMakeContextCurrent(dummy);

        gladLoadGL();

        glfwDestroyWindow(dummy);
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    }
}