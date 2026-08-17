#pragma once

#include "window/fps.hpp"
#include "window/cursor_ctx.hpp"
#include "window/window.hpp"
#include "window/win_io.hpp"

#include "scene/camera.hpp"
#include "scene/instances.hpp"

#include "gfx/renderer.hpp"
#include "gfx/buffer/mesh_buffer.hpp"
#include "gfx/buffer/instances_buffer.hpp"

#include "geometry/camera.hpp"
#include "geometry/mesh.hpp"
#include "geometry/vertex.hpp"


namespace engine {
    struct Engine {
        static void Init() { // ive got a feeling that this isnt the best away to go by things, but it works for now HACK?
            glfwInit();

            win::Window window = {
                1, 1, "dummy"
            };
            window.use();

            gladLoadGL();

        }
    };
}