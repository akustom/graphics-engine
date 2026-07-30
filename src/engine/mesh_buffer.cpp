#include "engine/mesh_buffer.hpp"

#include "gfx/mesh.hpp"
#include "gfx/vertex.hpp"


namespace engine {
    MeshBuffer::IndexData MeshBuffer::getMeshOffset(gfx::Mesh& mesh) const {
        return indexedMeshes[mesh.id];
    }

    void MeshBuffer::addMesh(gfx::Mesh& mesh) {
        // vertices
        if (verticesBatchData.size + mesh.vertices.size() > verticesBatchData.capacity) {
            verticesBatchData.capacity = 2 * std::max(verticesBatchData.size, static_cast<int>(mesh.vertices.size()));

            glw::VBO tempVBO;
            tempVBO.allocateBuffer<gfx::vertex>(verticesBatchData.capacity, GL_DYNAMIC_STORAGE_BIT);
            tempVBO.copyData<gfx::vertex>(vertexBuffer, verticesBatchData.size);

            vertexBuffer = std::move(tempVBO);
        }
        vertexBuffer.pushData(static_cast<int>(bytesof<gfx::vertex>()) * verticesBatchData.size, mesh.vertices);
        vertexFormat.attachBuffer(vertexBuffer, 0, 0, bytesof<gfx::vertex>());

        // indices
        if (indicesBatchData.size + mesh.indices.size() > indicesBatchData.capacity) {
            indicesBatchData.capacity = 2 * std::max(indicesBatchData.size, static_cast<int>(mesh.indices.size()));

            glw::EBO tempEBO;
            tempEBO.allocateBuffer<glm::uint>(indicesBatchData.capacity, GL_DYNAMIC_STORAGE_BIT);
            tempEBO.copyData<glm::uint>(indexBuffer, indicesBatchData.size);

            indexBuffer = std::move(tempEBO);
        }
        indexBuffer.pushData(static_cast<int>(bytesof<glm::uint>()) * indicesBatchData.size, mesh.indices);
        vertexFormat.attachBuffer(indexBuffer);
    }

    void MeshBuffer::indexMesh(gfx::Mesh& mesh) {
        addMesh(mesh);

        mesh.id = static_cast<int>(indexedMeshes.size());
        indexedMeshes.emplace_back(indicesBatchData.size, verticesBatchData.size);

        indexedMeshes[mesh.id].indexCount = static_cast<int>(mesh.indices.size());
        indexedMeshes[mesh.id].ebo_offset = indicesBatchData.size;
        indexedMeshes[mesh.id].vbo_offset = verticesBatchData.size;

        indicesBatchData.size  += static_cast<int>(mesh.indices.size());
        verticesBatchData.size += static_cast<int>(mesh.vertices.size());
    }

    glw::VAO& MeshBuffer::getVAO() {
        return vertexFormat;
    }
}