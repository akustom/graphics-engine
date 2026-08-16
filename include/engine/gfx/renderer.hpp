#pragma once

#include "engine/gfx/buffer/mesh_buffer.hpp"
#include "engine/gfx/buffer/instances_buffer.hpp"

namespace engine::scene {
    struct Instances;
}

namespace engine::gfx {
    struct Renderer {
        MeshBuffer& meshBuffer;
        InstancesBuffer& instancesBuffer;

        Renderer(MeshBuffer& mesh_buffer, InstancesBuffer& instances_buffer) : meshBuffer(mesh_buffer), instancesBuffer(instances_buffer) {}

        void render(geo::Mesh& mesh, scene::Instances& instances) const;
    };
}
