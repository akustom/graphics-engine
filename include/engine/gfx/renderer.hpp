#pragma once

#include "glw/primitive/render.hpp"
#include "engine/geometry/mesh.hpp"

#include "engine/gfx/buffer/render_batch.hpp"
#include <tracy/Tracy.hpp>

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

            auto vertexHandle = renderBatch.meshBuffer.vertexHandles[mesh.id];
            auto indexHandle = renderBatch.meshBuffer.indexHandles[mesh.id];
            auto instancesHandle = renderBatch.instancesBuffer.instancesHandles[instances.id];

            glw::drawInstancesBaseVertexBaseInstances(
                instancesHandle.count,
                indexHandle.count,
                indexHandle.bufferOffset,
                vertexHandle.bufferOffset,
                instancesHandle.bufferOffset);
        }
    };
}
