#pragma once

#include "glw/render.hpp"

#include "engine/gfx/buffer/render_batch.hpp"
#include "tracy/Tracy.hpp"

namespace engine::geo {
    struct Mesh;
}

namespace engine::scene {
    struct Instances;
}

namespace engine::gfx {
    template <typename T>
    struct Renderer {
        RenderBatch<T>& renderBatch;

        Renderer(RenderBatch<T>& render_batch) : renderBatch(render_batch) {}

        void render(geo::Mesh& mesh, scene::Instances& instances) const {
            ZoneScoped;
            renderBatch.renderFormat.bind();

            auto meshOffset = renderBatch.meshBuffer.getMeshOffset(mesh);
            auto instancesOffset = renderBatch.instancesBuffer.getInstancesOffset(instances);

            glw::drawInstancesBaseVertexBaseInstances(
                instancesOffset.instances_count,
                meshOffset.indexCount,
                meshOffset.ebo_offset,
                meshOffset.vbo_offset,
                instancesOffset.buffer_offset);
        }
    };
}
