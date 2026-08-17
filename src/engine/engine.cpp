#include "engine/engine.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace engine {
    void Engine::Init() {
        glfwInit();

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        win::Window window = {
            1, 1, "dummy"
        };
        window.use();

        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

        gladLoadGL();
    }
}