#include "engine/mesh_buffer.hpp"

#include "gfx/mesh.hpp"
#include "gfx/vertex.hpp"


namespace engine {
    MeshBuffer::IndexData MeshBuffer::getMeshOffset(gfx::Mesh& mesh) const {
        return indexedMeshes[mesh.id];
    }

    void MeshBuffer::pushVertices(std::vector<gfx::vertex>& vertices) {
        if (!indexedMeshes.empty()) {
            if (verticesBatchHeader.size + vertices.size() > verticesBatchHeader.capacity) {
                verticesBatchHeader.capacity = 2 * std::max(verticesBatchHeader.size, static_cast<int>(vertices.size()));

                glw::VBO tempVBO;
                tempVBO.allocateBuffer<gfx::vertex>(verticesBatchHeader.capacity, GL_DYNAMIC_STORAGE_BIT);
                tempVBO.copyData<gfx::vertex>(vertexBuffer, verticesBatchHeader.size);

                vertexBuffer = std::move(tempVBO);
                vertexFormat.attachBuffer(vertexBuffer, bindingLocation, 0, util::bytesof<gfx::vertex>());
            }
            vertexBuffer.pushData(static_cast<int>(util::bytesof<gfx::vertex>()) * verticesBatchHeader.size, vertices);

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
            if (indicesBatchHeader.size + indices.size() > indicesBatchHeader.capacity) {
                indicesBatchHeader.capacity = 2 * std::max(indicesBatchHeader.size, static_cast<int>(indices.size()));

                glw::EBO tempEBO;
                tempEBO.allocateBuffer<glm::uint>(indicesBatchHeader.capacity, GL_DYNAMIC_STORAGE_BIT);
                tempEBO.copyData<glm::uint>(indexBuffer, indicesBatchHeader.size);

                indexBuffer = std::move(tempEBO);
                vertexFormat.attachBuffer(indexBuffer);
            }
            indexBuffer.pushData(static_cast<int>(util::bytesof<glm::uint>()) * indicesBatchHeader.size, indices);

        } else {
            indexBuffer.allocateBuffer(indices);
            vertexFormat.attachBuffer(indexBuffer);
        }
    }

    void MeshBuffer::push(gfx::Mesh& mesh) {
        pushVertices(mesh.vertices);
        pushIndices(mesh.indices);
    }

    void MeshBuffer::index(gfx::Mesh& mesh) {
        push(mesh);

        mesh.id = static_cast<int>(indexedMeshes.size());
        indexedMeshes.emplace_back(
            static_cast<int>(mesh.indices.size()),
            indicesBatchHeader.size,
            verticesBatchHeader.size);

        indicesBatchHeader.size  += static_cast<int>(mesh.indices.size());
        verticesBatchHeader.size += static_cast<int>(mesh.vertices.size());
    }

    glw::VAO& MeshBuffer::getVAO() {
        return vertexFormat;
    }
}