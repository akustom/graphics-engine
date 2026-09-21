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
// profiler
#include <tracy/Tracy.hpp>
#include <tracy/TracyOpenGL.hpp>
// windows
#include <windows.h>
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")


using namespace engine;

int main_() {
    scene::Instances Particles;

    for (int i = 0; i < 1500; i++)
        Particles.createInstance({
            .pos  = {util::random(-10.0f, 10.0f), util::random(-10.0f, 10.0f),util::random(-10.0f, 10.0f)},
            .mass = 14982844642.0f
        });

    for (int i = 0; i < 2500; i++)
        phy::V_V::step<phy::gravity>(Particles, 1.0f/120.0f);

    return 0;
}

int main() {
    timeBeginPeriod(1);

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

    glw::ShaderProgram shaderProgram;
    shaderProgram.build(
        {SOURCE_DIR "assets/shaders/vertexShader.glsl", GL_VERTEX_SHADER},
        {SOURCE_DIR "assets/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER}
    );
    shaderProgram.use();


    geo::Mesh mesh1;
    geo::makePolyhedron(mesh1, 1.0f, 16, {1.0, 1.0, 1.0});

    scene::Instances Particles;

    Particles.createInstance({{2,0, 0}});
    Particles.createInstance({{-2,0, 0}});
    Particles.createInstance({{0, 2, 0}});
    Particles.createInstance({{0,-2, 0}});
    Particles.createInstance({{0, 0, 2}});
    Particles.createInstance({{0, 0,-2}});


    gfx::RenderBatch<geo::vertex> renderBatch = {0, 1};

    auto square_h = renderBatch.index(mesh1);
    auto particles_h  = renderBatch.index(Particles);


    scene::Camera camera = {0};
    camera.use(window);
    camera.setSpeed(20);

    window.setFPS(144);

    while (!glfwWindowShouldClose(window.glfw())) {
        ZoneScopedN("Main Frame");
        window.startFrame(0.07f, 0.07f, 0.07f, 1.0f);

        auto dt = static_cast<float>(window.getFrameTime());

        camera.processMouse(window);
        camera.processKeyboard(window, dt);
        camera.sendUpdate(window);

        if (window.isKeyPressed(GLFW_KEY_P))
            Particles.createInstance({
                .pos  = {util::random(-10.0f, 10.0f), util::random(-10.0f, 10.0f),util::random(-10.0f, 10.0f)},
                .mass = 14982844642.0f
            });

        if (window.isKeyPressed(GLFW_KEY_X))
            Particles.clear();

        phy::V_V::step<phy::gravity>(Particles, 1.0f/120.0f);

        renderBatch.update(particles_h, Particles);
        renderBatch.render(square_h, particles_h);

        window.endFrame();
        FrameMark;
    }

    timeEndPeriod(1);
    return 0;
}