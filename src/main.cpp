#include <iostream>
#include <string>
#include <vector>
// opengl
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// glm
#include <glm/gtc/type_ptr.hpp>
// just my libs
#include "glw/core/glw.hpp"
#include "engine/engine.hpp"

#include "util.hpp"

#include <tracy/Tracy.hpp>
#include <tracy/TracyOpenGL.hpp>


using namespace engine;

int main() {
    Engine::Init();

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

    glw::HandleIssuer registry;
    for (int i = 0; i < 5; i++) {
        auto* foo = new auto(registry.getUniqueHandle());
        util::print(foo->id);
    }

    util::print("----------");
    for (const auto& i : registry.oldFreeHandles) {
        util::print(i);
    }



    geo::Mesh square;
    geo::makePolyhedron(square, 1.0f, 32, {1.0, 1.0, 1.0});

    geo::Mesh cube;
    geo::makePolyhedron(cube, 1.0f, 8, {1.0, 0.0, 0.0});

    geo::Mesh platform;
    platform.vertices = {
            {{10, 0,  10}, {1, 0, 0}},
            {{10, 0, -10}, {0, 1, 0}},
            {{-10, 0, 10}, {0, 0, 1}},
            {{-10, 0,-10}, {1, 1, 1}},
    };
    platform.indices = {2, 0, 1, 2, 3, 1};


    scene::Instances squareParticles;
    squareParticles.createInstance({2, 0, 0});
    squareParticles.createInstance({-2,0, 0});
    squareParticles.createInstance({0, 2, 0});
    squareParticles.createInstance({0,-2, 0});
    squareParticles.createInstance({0, 0, 2});
    squareParticles.createInstance({0, 0,-2});

    scene::Instances cubeParticles;
    while (cubeParticles.positions.size() < 10000) {
        cubeParticles.createInstance({
            util::random(-1000.0f, 1000.0f),
            util::random(-1000.0f, 1000.0f),
            util::random(-1000.0f, 1000.0f)}
            );
    }

    scene::Instances platformPlace;
    platformPlace.createInstance({0, -5, 0});

    while (platformPlace.positions.size() < 0) {
        platformPlace.createInstance({
            util::random(-1000.0f, 1000.0f),
            util::random(-1000.0f, 1000.0f),
            util::random(-1000.0f, 1000.0f)}
            );
    }


    int squareHandle = renderBatch.index(square);
    int cubeHandle   = renderBatch.index(cube);
    int platformHandle = renderBatch.index(platform);

    int sqrInstancesHandle  = renderBatch.index(squareParticles);
    int cubeInstancesHandle = renderBatch.index(cubeParticles);
    int platformInstancesHandle = renderBatch.index(platformPlace);


    scene::Camera camera = {0};
    camera.use(window);
    camera.setSpeed(10);

    window.setFPS(144);

    while (!glfwWindowShouldClose(window.glfw_window)) {
        ZoneScopedN("Main Frame");
        window.startFrame(0.07f, 0.07f, 0.07f, 1.0f);

        auto dt = static_cast<float>(window.getFrameTime());

        camera.processMouse(window);
        camera.processKeyboard(window, dt);
        camera.sendUpdate(window);

        renderer.render(squareHandle, sqrInstancesHandle);
        renderer.render(cubeHandle,   cubeInstancesHandle);
        renderer.render(platformHandle, platformInstancesHandle);

        window.endFrame();
        FrameMark;
    }

    return 0;
}