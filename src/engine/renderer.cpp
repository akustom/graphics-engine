#include "engine/renderer.hpp"

#include "gfx/mesh.hpp"
#include "glw/render.hpp"

#include "engine/mesh_buffer.hpp"

#include "tracy/Tracy.hpp"


namespace engine {
    void Renderer::bindToBuffer(MeshBuffer& buffer) {
        meshBuffer = &buffer;
    }

    void Renderer::render(Instances& instances) const {
        ZoneScoped;
        if (instances.mesh->id == -1)
            meshBuffer->indexMesh(*instances.mesh);

        meshBuffer->getVAO().bind();

        MeshBuffer::IndexData meshOffset = meshBuffer->getMeshOffset(*instances.mesh);
        glw::drawInstancesBaseVertex(
            instances.instanceCount,
            meshOffset.indexCount,
            meshOffset.ebo_offset,
            meshOffset.vbo_offset
            );
    }
}
