#pragma once

#include "glw/primitive/render.hpp"

#include "engine/gfx/buffer/render_batch.hpp"
#include <tracy/Tracy.hpp>

namespace engine::gfx {
    template <typename T>
    struct Renderer {
        RenderBatch<T>& renderBatch;

        Renderer(RenderBatch<T>& render_batch) : renderBatch(render_batch) {}

        void render(int meshHandle, int instancesHandle) const {
            ZoneScoped;
            renderBatch.renderFormat.bind();

            auto vertexHeader = renderBatch.meshBuffer.vertexHeaders[meshHandle];
            auto indexHeader  = renderBatch.meshBuffer.indexHeaders[meshHandle];
            auto instancesHeader = renderBatch.instancesBuffer.instancesHeaders[instancesHandle];

            glw::drawInstancesBaseVertexBaseInstances(
                instancesHeader.count,
                indexHeader.count,
                indexHeader.bufferOffset,
                vertexHeader.bufferOffset,
                instancesHeader.bufferOffset);
        }
    };
}
