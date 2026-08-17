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
    Engine::Init();

    win::Window::setHints(4, 6);

    win::Window window = {
        960, 540, "gravity sim babyyyy"
    };

    window.use();
    window.setVSync(false);

    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    window.setCursorPosCallback(win::cursor_pos_callback);
    window.setMouseButtonCallback(win::mouse_button_callback);

    gfx::setViewport(window);
    gfx::enableDepthTest(true);

    gfx::RenderBatch<geo::vertex> renderBatch = {0, 1};
    gfx::Renderer renderer = {renderBatch};


    glw::ShaderProgram shaderProgram;
    shaderProgram.build(
        {SOURCE_DIR "assets/shaders/vertexShader.glsl", GL_VERTEX_SHADER},
        {SOURCE_DIR "assets/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER}
    );
    shaderProgram.use();


    geo::Mesh square;
    geo::makePolyhedron(square, 1.0f, 8, {1.0, 1.0, 1.0});

    geo::Mesh cube;
    geo::makePolyhedron(cube, 1.0f, 6, {1.0, 0.0, 0.0});

    geo::Mesh platform;
    platform.vertices = {
                {{10, 0, 10}, {1, 0, 0}},
                {{10, 0, -10}, {0, 1, 0}},
                {{-10, 0, 10}, {0, 0, 1}},
                {{-10, 0, -10}, {1, 1, 1}}
    };
    platform.indices = {2, 0, 1, 2, 3, 1};


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

    scene::Instances platformPlace;
    platformPlace.createInstance({0, -5, 0});

    while (platformPlace.positions.size() < 10000) {
        platformPlace.createInstance({
            util::random(-1000.0f, 1000.0f),
            util::random(-1000.0f, 1000.0f),
            util::random(-1000.0f, 1000.0f)}
            );
    }


    renderBatch.index(square);
    renderBatch.index(cube);
    renderBatch.index(platform);

    renderBatch.index(particles);
    renderBatch.index(platformPlace);


    scene::Camera camera = {0};
    camera.use(window);
    camera.setSpeed(100);

    window.setFPS(144);

    while (!glfwWindowShouldClose(window.glfw_window)) {
        ZoneScopedN("Main Frame");
        window.startFrame(0.07f, 0.07f, 0.07f, 1.0f);

        auto dt = static_cast<float>(window.getFrameTime());

        camera.processMouse(window);
        camera.processKeyboard(window, dt);
        camera.sendUpdate(window);

        renderer.render(square, particles);
        renderer.render(cube, particles);
        renderer.render(platform, platformPlace);

        window.endFrame();
        FrameMark;
    }

    return 0;
}