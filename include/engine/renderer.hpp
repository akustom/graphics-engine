#pragma once

#include "gfx/mesh.hpp"
#include "engine/mesh_buffer.hpp"
#include "engine/instances.hpp"


namespace engine {
    struct Renderer {
        MeshBuffer* meshBuffer;

        Renderer(MeshBuffer& buffer) : meshBuffer(&buffer) {}

        void bindToBuffer(MeshBuffer& buffer);
        void render(Instances& instances) const;
    };
}
