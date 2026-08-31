#pragma once

#include <tracy/Tracy.hpp>

#include "glw/core/render.hpp"

#include "engine/core/handle_issuer.hpp"
#include "engine/gfx/buffer/render_batch.hpp"


namespace engine::gfx {
    template <typename T>
    struct Renderer {
        RenderBatch<T>& renderBatch;

        Renderer(RenderBatch<T>& render_batch) : renderBatch(render_batch) {}

        void render(const core::Handle& meshHandle, const core::Handle& instancesHandle) const {
            ZoneScoped;
            renderBatch.renderFormat.bind();

            const glw::IndexHeader vertexHeader = renderBatch.meshBuffer[meshHandle].at(0);
            const glw::IndexHeader indexHeader  = renderBatch.meshBuffer[meshHandle].at(1);
            const glw::IndexHeader instancesHeader = renderBatch.instancesBuffer[instancesHandle].at(0);

            glw::drawInstancesBaseVertexBaseInstances(
                instancesHeader.count,
                indexHeader.count,
                indexHeader.bufferOffset,
                vertexHeader.bufferOffset,
                instancesHeader.bufferOffset);
        }
    };
}
