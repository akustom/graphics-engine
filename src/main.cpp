#include <iostream>
#include <string>
#include <vector>
// opengl
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// glm
#include "glm/gtc/type_ptr.hpp"
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


    glw::VAO test;
    MeshBuffer meshBuffer = {test, 0};
    InstancesBuffer instancesBuffer = {test, 1};

    Renderer renderer = {meshBuffer, instancesBuffer};


    glw::ShaderProgram shaderProgram;
    shaderProgram.build(
        {SOURCE_DIR "assets/shaders/vertexShader.glsl", GL_VERTEX_SHADER},
        {SOURCE_DIR "assets/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER}
    );
    shaderProgram.use();

    gfx::Mesh square;
    gfx::makePolyhedron(square, 1.0f, 16, {1.0, 1.0, 1.0});

    gfx::Mesh cube;
    gfx::makePolyhedron(cube, 1.0f, 6, {1.0, 0.0, 0.0});


    Instances particles;
    particles.createInstance({2, 0, 0});
    particles.createInstance({-2, 0, 0});
    particles.createInstance({0, 2, 0});
    particles.createInstance({0, -2, 0});
    particles.createInstance({0, 0, 2});
    particles.createInstance({0, 0, -2});

    while (particles.positions.size() < 50) {
        particles.createInstance({
            util::random(-10.0f, 10.0f),
            util::random(-10.0f, 10.0f),
            util::random(-10.0f, 10.0f)}
            );
    }


    Camera camera = {0};
    camera.use(window);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);


    meshBuffer.index(square);
    meshBuffer.index(cube);
    instancesBuffer.index(particles);

    test.bind();

    window.setFPS(144);

    while (!glfwWindowShouldClose(window.glfw_window)) {
        ZoneScopedN("Main Frame");
        window.startFrame(0.07f, 0.07f, 0.07f, 1.0f);

        auto dt = static_cast<float>(window.getFrameTime());

        camera.processMouse(window);
        camera.processKeyboard(window, dt);
        camera.sendUpdate();

        renderer.render(cube, particles);
        renderer.render(square, particles);
        //particles.bindToMesh(cube);
        //renderer.render(particles);

        window.endFrame();
        FrameMark;
    }

    return 0;
}