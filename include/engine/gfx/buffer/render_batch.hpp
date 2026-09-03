#pragma once

#include "glw/core/vao.hpp"
#include "engine/core/registry.hpp"
#include "engine/gfx/buffer/mesh_buffer.hpp"
#include "engine/gfx/buffer/instances_buffer.hpp"

#include <tracy/Tracy.hpp>


namespace engine::gfx {
    template <typename T>
    struct RenderBatch {
        glw::VAO renderFormat;
        MeshBuffer meshBuffer;
        InstancesBuffer instancesBuffer;

        RenderBatch(int vertex_loc,  int instance_loc) :
            meshBuffer(renderFormat, vertex_loc),
            instancesBuffer(renderFormat, instance_loc) {

            renderFormat.formatAttribute<T, float>(0, vertex_loc, GL_FLOAT);

            renderFormat.formatAttribute(3, instance_loc, 4, GL_FLOAT, 0); // todo, abstract this away or smth, make it like the top one's implementation
            renderFormat.setAttributeDivisor(instance_loc, 1);
        }

        core::rHandle index(geo::Mesh& mesh) {
            ZoneScopedN("RenderBatch::index, mesh");
            return meshBuffer.index(mesh);
        }
        core::rHandle index(scene::Instances& instances) {
            ZoneScopedN("RenderBatch::index, instances");
            return instancesBuffer.index(instances);
        }
    };
}