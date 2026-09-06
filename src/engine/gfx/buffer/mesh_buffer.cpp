#include "engine/gfx/buffer/mesh_buffer.hpp"

#include "engine/core/registry.hpp"
#include "engine/geometry/mesh.hpp"
#include "engine/geometry/vertex.hpp"


namespace engine::gfx {
    const glw::HeaderPair<2>& MeshBuffer::operator[](core::rHandle handle) const {
        return registry.at(handle);
    }

    void MeshBuffer::pushVertices(std::vector<geo::vertex>& vertices) {
        vertexHeaders.push_back(vertices, vertexFormat,
            vertexHeaders.getBuffer(),
            bindingPoint, 0,
            sizeof(geo::vertex));
    }

    void MeshBuffer::pushIndices(std::vector<glm::uint>& indices) {
        indexHeaders.push_back(indices, vertexFormat, indexHeaders.getBuffer());
    }

    void MeshBuffer::push(geo::Mesh& mesh) {
        pushVertices(mesh.vertices);
        pushIndices(mesh.indices);
    }

    core::rHandle MeshBuffer::index(geo::Mesh& mesh) {
        push(mesh);

        auto handle = registry.create(glw::HeaderPair<2>{
            vertexHeaders.back(),
            indexHeaders.back()});

        return handle;
    }
}