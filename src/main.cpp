#include <iostream>
#include <string>
#include <vector>
#include <random>
// opengl
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// glm
#include <glm/gtc/type_ptr.hpp>
// just my libs
#include "glw/glw.hpp"
#include "gfx/gfx.hpp"
#include "win/win.hpp"
#include "engine/engine.hpp"
#include "physics/phy.hpp"

#include "util.hpp"

#include "tracy/Tracy.hpp"
#include <tracy/TracyOpenGL.hpp>


using namespace engine;

int main() {
    glfwInit();

    win::Window window{
        4, 6,
        960, 540, "gravity sim babyyyy"
    };
    window.use();
    glfwSwapInterval(0);

    glfwSetFramebufferSizeCallback(window.glfw_window, [](GLFWwindow* win, const int w, const int h) {
        glViewport(0, 0, w, h);
    });

    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    window.setCursorPosCallback(io::cursor_pos_callback);
    window.setMouseButtonCallback(io::mouse_button_callback);


    gladLoadGL();

    glViewport(0, 0, 960, 540);


    MeshBuffer meshBuffer;

    Renderer renderer = {meshBuffer};


    glw::ShaderProgram shaderProgram;
    shaderProgram.build(
        {SOURCE_DIR "assets/shaders/vertexShader.glsl", GL_VERTEX_SHADER},
        {SOURCE_DIR "assets/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER}
    );
    shaderProgram.use();


    gfx::Mesh square;
    gfx::makePolyhedron(square, 1.0f, 16, {1.0, 1.0, 1.0});

    gfx::Mesh cube;
    gfx::makePolyhedron(cube, 1.0f, 4, {1.0, 0.0, 0.0});


    phy::Particles particles;
    particles.createParticle(0, {0, 0, 0});
    particles.createParticle(0, {2, 0, 0});
    particles.createParticle(0, {-2, 0, 0});
    particles.createParticle(0, {0, 2, 0});
    particles.createParticle(0, {0, -2, 0});
    particles.createParticle(0, {0, 0, 2});
    particles.createParticle(0, {0, 0, -2});


    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution disX(-1000.0f, 1000.0f);
    std::uniform_real_distribution disY(-1000.0f, 1000.0f);
    std::uniform_real_distribution disZ(-1000.0f, 1000.0f);

    while (particles.positions.size() < 0) {
        particles.createParticle(0, {disX(gen), disY(gen), disZ(gen)});
    }


    glw::VBO instanceVBO;
    instanceVBO.allocateBuffer(particles.positions);
    meshBuffer.getVAO().attachBuffer(instanceVBO, 1, 0, bytesof<glm::vec4>());


    Camera camera = {0};
    camera.use(window);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    while (!glfwWindowShouldClose(window.glfw_window)) {
        FrameTimer::setFPS(144);
        ZoneScopedN("Main Frame");

        float dt = FrameTimer::getFrameTime();

        glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.processMouse(window);
        camera.processKeyboard(window, dt);
        camera.sendUpdate();

        renderer.Mesh(square, static_cast<int>(particles.positions.size()));
        //Render.Mesh(cube,   static_cast<int>(particles.positions.size()));

        window.cursorContext.clearOffsets(); // idea create an end frame method in window to clear offsets, swap buffers, poll events, etc
        glfwSwapBuffers(window.glfw_window);
        glfwPollEvents();
        FrameMark;
    }

    glfwTerminate();
    return 0;
}