#pragma once

#include "engine/mesh_buffer.hpp"
#include "engine/instances.hpp"


namespace engine {
    struct Renderer {
        MeshBuffer* meshBuffer;

        Renderer(MeshBuffer& buffer) : meshBuffer(&buffer) {}

        void bindToBuffer(MeshBuffer& buffer);
        void render(gfx::Mesh& mesh, Instances& instances) const;
    };
}
