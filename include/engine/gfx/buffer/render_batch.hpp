#pragma once

#include "glw/vao.hpp"
#include "engine/gfx/buffer/mesh_buffer.hpp"
#include "engine/gfx/buffer/instances_buffer.hpp"


namespace engine::gfx {
    struct RenderBatch {
        glw::VAO renderFormat;
        MeshBuffer meshBuffer;
        InstancesBuffer instancesBuffer;

        RenderBatch(int mesh_loc, int instance_loc) :
            meshBuffer(renderFormat, mesh_loc),
            instancesBuffer(renderFormat, instance_loc)
        {}

        void index(geo::Mesh& mesh);
        void index(scene::Instances& instances);
    };
}