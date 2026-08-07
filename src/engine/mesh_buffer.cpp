#include "engine/mesh_buffer.hpp"

#include "gfx/mesh.hpp"
#include "gfx/vertex.hpp"


namespace engine {
    MeshBuffer::IndexData MeshBuffer::getMeshOffset(gfx::Mesh& mesh) const {
        return indexedMeshes[mesh.id];
    }

    void MeshBuffer::pushVertices(std::vector<gfx::vertex>& vertices) {
        if (!indexedMeshes.empty()) {
            if (verticesBatchData.size + vertices.size() > verticesBatchData.capacity) {
                verticesBatchData.capacity = 2 * std::max(verticesBatchData.size, static_cast<int>(vertices.size()));

                glw::VBO tempVBO;
                tempVBO.allocateBuffer<gfx::vertex>(verticesBatchData.capacity, GL_DYNAMIC_STORAGE_BIT);
                tempVBO.copyData<gfx::vertex>(vertexBuffer, verticesBatchData.size);

                vertexBuffer = std::move(tempVBO);
                vertexFormat.attachBuffer(vertexBuffer, bindingLocation, 0, util::bytesof<gfx::vertex>());
            }
            vertexBuffer.pushData(static_cast<int>(util::bytesof<gfx::vertex>()) * verticesBatchData.size, vertices);

        } else {
            vertexBuffer.allocateBuffer(vertices);
            vertexFormat.attachBuffer(
                vertexBuffer,
                bindingLocation, 0,
                util::bytesof<gfx::vertex>()
                );
        }
    }

    void MeshBuffer::pushIndices(std::vector<glm::uint>& indices) {
        if (!indexedMeshes.empty()) {
            if (indicesBatchData.size + indices.size() > indicesBatchData.capacity) {
                indicesBatchData.capacity = 2 * std::max(indicesBatchData.size, static_cast<int>(indices.size()));

                glw::EBO tempEBO;
                tempEBO.allocateBuffer<glm::uint>(indicesBatchData.capacity, GL_DYNAMIC_STORAGE_BIT);
                tempEBO.copyData<glm::uint>(indexBuffer, indicesBatchData.size);

                indexBuffer = std::move(tempEBO);
                vertexFormat.attachBuffer(indexBuffer);
            }
            indexBuffer.pushData(static_cast<int>(util::bytesof<glm::uint>()) * indicesBatchData.size, indices);

        } else {
            indexBuffer.allocateBuffer(indices);
            vertexFormat.attachBuffer(indexBuffer);
        }
    }

    void MeshBuffer::push(gfx::Mesh& mesh) {
        pushVertices(mesh.vertices);
        pushIndices(mesh.indices);
    }

    void MeshBuffer::indexMesh(gfx::Mesh& mesh) {
        push(mesh);

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