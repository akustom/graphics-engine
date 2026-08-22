#include "engine/gfx/buffer/mesh_buffer.hpp"

#include "engine/geometry/mesh.hpp"
#include "engine/geometry/vertex.hpp"


namespace engine::gfx {
    void MeshBuffer::pushVertices(std::vector<geo::vertex>& vertices) {
        vertexHandles.push_back(vertices, [this] {
            vertexFormat.attachBuffer(
                vertexHandles.getBuffer(),
                bindingPoint, 0,
                util::bytesof<geo::vertex>()
                );
        });
    }

    void MeshBuffer::pushIndices(std::vector<glm::uint>& indices) {
        indexHandles.push_back(indices, [this] {
            vertexFormat.attachBuffer(indexHandles.getBuffer());
        });
    }

    void MeshBuffer::push(geo::Mesh& mesh) {
        pushVertices(mesh.vertices);
        pushIndices(mesh.indices);
    }

    void MeshBuffer::index(geo::Mesh& mesh) {
        push(mesh);
        mesh.id = nextFreeIndex;
        nextFreeIndex++;
    }
}