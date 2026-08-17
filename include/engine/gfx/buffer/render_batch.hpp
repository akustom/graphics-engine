#pragma once

#include "glw/vao.hpp"
#include "engine/gfx/buffer/mesh_buffer.hpp"
#include "engine/gfx/buffer/instances_buffer.hpp"


namespace engine::gfx {
    struct RenderBatch {
        glw::VAO renderFormat;
        MeshBuffer meshBuffer;
        InstancesBuffer instancesBuffer;

        RenderBatch(int mesh_loc, int instance_loc) :  // TODO: refactor this to be more flexible with its formatting (use boost)
            meshBuffer(renderFormat, mesh_loc),
            instancesBuffer(renderFormat, instance_loc) {

            renderFormat.formatAttribute(0, mesh_loc, 3, GL_FLOAT, offsetof(geo::vertex, pos));
            renderFormat.formatAttribute(1, mesh_loc, 3, GL_FLOAT, offsetof(geo::vertex, color));
            renderFormat.formatAttribute(2, mesh_loc, 3, GL_FLOAT, offsetof(geo::vertex, normal));

            renderFormat.formatAttribute(3, instance_loc, 4, GL_FLOAT, 0);
            renderFormat.setAttributeDivisor(instance_loc, 1);
        }

        void index(geo::Mesh& mesh);
        void index(scene::Instances& instances);
    };
}