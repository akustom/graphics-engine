#include "engine/gfx/buffer/mesh_buffer.hpp"

#include "engine/geometry/mesh.hpp"
#include "engine/geometry/vertex.hpp"


namespace engine::gfx {
    MeshBuffer::IndexData MeshBuffer::getMeshOffset(geo::Mesh& mesh) const {
        return indexedMeshes[mesh.id];
    }

    void MeshBuffer::pushVertices(std::vector<geo::vertex>& vertices) {
        if (indicesBatchHeader.size) {
            if (verticesBatchHeader.size + vertices.size() > verticesBatchHeader.capacity) {
                verticesBatchHeader.capacity = 2 * std::max(verticesBatchHeader.size, static_cast<int>(vertices.size()));

                glw::VBO tempVBO;
                tempVBO.allocateBuffer<geo::vertex>(verticesBatchHeader.capacity, GL_DYNAMIC_STORAGE_BIT);
                tempVBO.copyData<geo::vertex>(vertexBuffer, verticesBatchHeader.size);

                vertexBuffer = std::move(tempVBO);
                vertexFormat.attachBuffer(vertexBuffer, bindingPoint, 0, util::bytesof<geo::vertex>());
            }
            vertexBuffer.pushData(static_cast<int>(util::bytesof<geo::vertex>()) * verticesBatchHeader.size, vertices);

        } else {
            vertexBuffer.allocateBuffer(vertices);
            vertexFormat.attachBuffer(
                vertexBuffer,
                bindingPoint, 0,
                util::bytesof<geo::vertex>()
                );
        }
    }

    void MeshBuffer::pushIndices(std::vector<glm::uint>& indices) {
        if (indicesBatchHeader.size) {
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

    void MeshBuffer::push(geo::Mesh& mesh) {
        pushVertices(mesh.vertices);
        pushIndices(mesh.indices);
    }

    void MeshBuffer::index(geo::Mesh& mesh) {
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