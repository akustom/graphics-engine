#pragma once

#include "core/registry.hpp"

#include "window/fps.hpp"
#include "window/cursor_ctx.hpp"
#include "window/window.hpp"
#include "window/win_io.hpp"

#include "scene/camera.hpp"
#include "scene/instances.hpp"

#include "gfx/renderer.hpp"
#include "gfx/render_state.hpp"
#include "gfx/buffer/mesh_buffer.hpp"
#include "gfx/buffer/instances_buffer.hpp"

#include "geometry/camera.hpp"
#include "geometry/mesh.hpp"
#include "geometry/vertex.hpp"


namespace engine {
    struct Engine {
        static void Init();
    };
}