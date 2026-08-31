#include "engine/gfx/buffer/mesh_buffer.hpp"

#include "engine/geometry/mesh.hpp"
#include "engine/geometry/vertex.hpp"


namespace engine::gfx {
    const glw::HeaderPair<2>& MeshBuffer::operator[](const core::Handle& handle) const {
        return registry.at(handle);
    }

    void MeshBuffer::pushVertices(std::vector<geo::vertex>& vertices) {
        vertexHeaders.push_back(vertices, vertexFormat,
            vertexHeaders.getBuffer(),
            bindingPoint, 0,
            util::bytesof<geo::vertex>());
    }

    void MeshBuffer::pushIndices(std::vector<glm::uint>& indices) {
        indexHeaders.push_back(indices, vertexFormat, indexHeaders.getBuffer());
    }

    void MeshBuffer::push(geo::Mesh& mesh) {
        pushVertices(mesh.vertices);
        pushIndices(mesh.indices);
    }

    const core::Handle& MeshBuffer::index(geo::Mesh& mesh) {
        push(mesh);

        auto [it, inserted] = registry.emplace(
            issuer.getUnique(),
            glw::HeaderPair{vertexHeaders.back(), indexHeaders.back()}
        );

        return it->first;
    }
}