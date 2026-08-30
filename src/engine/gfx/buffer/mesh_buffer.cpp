#include "engine/gfx/buffer/mesh_buffer.hpp"

#include "engine/geometry/mesh.hpp"
#include "engine/geometry/vertex.hpp"


namespace engine::gfx {
    int MeshBuffer::pushVertices(std::vector<geo::vertex>& vertices) {
        return vertexHeaders.push_back(vertices, vertexFormat,
            vertexHeaders.getBuffer(),
            bindingPoint, 0,
            util::bytesof<geo::vertex>());
    }

    int MeshBuffer::pushIndices(std::vector<glm::uint>& indices) {
        return indexHeaders.push_back(indices, vertexFormat, indexHeaders.getBuffer());
    }

    int MeshBuffer::push(geo::Mesh& mesh) {
        int ver = pushVertices(mesh.vertices);
        int ind = pushIndices(mesh.indices);

        // do something like notify a synchronization mismatch
        return ver;
    }

    int MeshBuffer::index(geo::Mesh& mesh) {
        return push(mesh);
    }
}