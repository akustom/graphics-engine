#pragma once

#include "engine/mesh_buffer.hpp"
#include "engine/instances_buffer.hpp"


namespace engine {
    struct Renderer {
        MeshBuffer& meshBuffer;
        InstancesBuffer& instancesBuffer;

        Renderer(MeshBuffer& mesh_buffer, InstancesBuffer& instances_buffer) : meshBuffer(mesh_buffer), instancesBuffer(instances_buffer) {}

        void render(gfx::Mesh& mesh, Instances& instances) const;
    };
}
