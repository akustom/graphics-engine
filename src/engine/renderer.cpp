#include "engine/renderer.hpp"

#include "gfx/vertex.hpp"
#include "glw/render.hpp"
#include "util.hpp"

#include "engine/mesh_buffer.hpp"

#include "tracy/Tracy.hpp"


namespace engine {
    void Renderer::bindToBuffer(MeshBuffer& buffer) {
        meshBuffer = &buffer;
    }

    void Renderer::Mesh(gfx::Mesh& mesh, const int instances) const {
        ZoneScoped;
        if (mesh.id == -1)
            meshBuffer->indexMesh(mesh);

        meshBuffer->getVAO().bind();

        MeshBuffer::IndexData meshOffset = meshBuffer->getMeshOffset(mesh);
        glw::drawInstancesBaseVertex(
            instances,
            meshOffset.indexCount,
            meshOffset.ebo_offset,
            meshOffset.vbo_offset
            );
    }
}
