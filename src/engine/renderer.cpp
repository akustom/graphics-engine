#include "engine/renderer.hpp"

#include "gfx/vertex.hpp"
#include "glw/render.hpp"
#include "util.hpp"

#include "engine/mesh_buffer.hpp"

#include "tracy/Tracy.hpp"


namespace engine {
    void Renderer::Mesh(gfx::Mesh& mesh, const int instances, MeshBuffer& mesh_buffer) {
        if (mesh.id == -1)
            mesh_buffer.indexMesh(mesh);

        mesh_buffer.getVAO().bind();

        MeshBuffer::IndexData meshOffset = mesh_buffer.getMeshOffset(mesh);
        glw::drawInstancesBaseVertex(
            instances,
            meshOffset.indexCount,
            meshOffset.ebo_offset,
            meshOffset.vbo_offset
            );
    }
}
