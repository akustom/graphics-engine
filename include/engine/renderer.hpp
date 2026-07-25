#pragma once

#include <vector>

#include "glm/fwd.hpp"

#include "engine/mesh_buffer.hpp"
#include "gfx/mesh.hpp"


namespace engine {
    struct Renderer {
        static void Mesh(gfx::Mesh& mesh, int instances, MeshBuffer& mesh_buffer);
    };
}
