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
#include "engine/engine.hpp"

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
    window.setCursorPosCallback(win::cursor_pos_callback);
    window.setMouseButtonCallback(win::mouse_button_callback);


    gladLoadGL();

    glViewport(0, 0, 960, 540);


    glw::VAO test;
    gfx::MeshBuffer meshBuffer = {test, 0};
    gfx::InstancesBuffer instancesBuffer = {test, 1};

    gfx::Renderer renderer = {meshBuffer, instancesBuffer};


    glw::ShaderProgram shaderProgram;
    shaderProgram.build(
        {SOURCE_DIR "assets/shaders/vertexShader.glsl", GL_VERTEX_SHADER},
        {SOURCE_DIR "assets/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER}
    );
    shaderProgram.use();

    geo::Mesh square;
    geo::makePolyhedron(square, 1.0f, 16, {1.0, 1.0, 1.0});

    geo::Mesh cube;
    geo::makePolyhedron(cube, 1.0f, 6, {1.0, 0.0, 0.0});

    scene::Instances particles;
    particles.createInstance({2, 0, 0});
    particles.createInstance({-2, 0, 0});
    particles.createInstance({0, 2, 0});
    particles.createInstance({0, -2, 0});
    particles.createInstance({0, 0, 2});
    particles.createInstance({0, 0, -2});

    while (particles.positions.size() < 100000) {
        particles.createInstance({
            util::random(-1000.0f, 1000.0f),
            util::random(-1000.0f, 1000.0f),
            util::random(-1000.0f, 1000.0f)}
            );
    }


    geo::Mesh platform;
    platform.vertices = {
            {{10, 0, 10}, {1, 0, 0}},
            {{10, 0, -10}, {0, 1, 0}},
            {{-10, 0, 10}, {0, 0, 1}},
            {{-10, 0, -10}, {1, 1, 1}}
    };
    platform.indices = {2, 0, 1, 2, 3, 1};

    scene::Instances platformPlace;
    platformPlace.createInstance({0, 10, 0});


    scene::Camera camera = {0};
    camera.use(window);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);


    meshBuffer.index(square);
    meshBuffer.index(cube);
    meshBuffer.index(platform);
    instancesBuffer.index(particles);
    instancesBuffer.index(platformPlace);

    test.bind();

    window.setFPS(144);

    while (!glfwWindowShouldClose(window.glfw_window)) {
        ZoneScopedN("Main Frame");
        window.startFrame(0.07f, 0.07f, 0.07f, 1.0f);

        auto dt = static_cast<float>(window.getFrameTime());

        camera.processMouse(window);
        camera.processKeyboard(window, dt);
        camera.sendUpdate();

        renderer.render(square, particles);
        renderer.render(cube, particles);
        renderer.render(platform, platformPlace);

        window.endFrame();
        FrameMark;
    }

    return 0;
}