#pragma once

#include <tracy/Tracy.hpp>

#include "glw/core/render.hpp"

#include "engine/core/registry.hpp"
#include "engine/gfx/buffer/render_batch.hpp"


namespace engine::gfx {
    template <typename T>
    struct Renderer {
        RenderBatch<T>& renderBatch;

        Renderer(RenderBatch<T>& render_batch) : renderBatch(render_batch) {}

        void render(core::rHandle meshHandle, core::rHandle instancesHandle) const {
            ZoneScoped;
            renderBatch.renderFormat.bind();

            const glw::IndexHeader vertexHeader = renderBatch.meshBuffer[meshHandle][0];
            const glw::IndexHeader indexHeader  = renderBatch.meshBuffer[meshHandle][1];

            const glw::IndexHeader instancesHeader = renderBatch.instancesBuffer[instancesHandle][0];

            glw::drawInstancesBaseVertexBaseInstances(
                instancesHeader.count,
                indexHeader.count,
                indexHeader.bufferOffset,
                vertexHeader.bufferOffset,
                instancesHeader.bufferOffset);
        }
    };
}
