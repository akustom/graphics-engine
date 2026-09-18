#include "engine/gfx/buffer/mesh_buffer.hpp"

#include "engine/core/registry.hpp"
#include "engine/geometry/mesh.hpp"
#include "engine/geometry/vertex.hpp"


namespace engine::gfx {
    glw::HeaderPair<2> MeshBuffer::operator[](core::Handle handle) const {
        return {
            vertexHeaders[registry.at(handle).vertex_i],
            indexHeaders[registry.at(handle).index_i]};
    }

    core::Handle MeshBuffer::index(geo::Mesh& mesh) {
        push(mesh);

        auto handle = registry.push({
            static_cast<uint32_t>(vertexHeaders.size()) - 1,
            static_cast<uint32_t>(indexHeaders.size())  - 1});

        return handle;
    }

    void MeshBuffer::modify(core::Handle handle, geo::Mesh& mesh) {
        vertexHeaders.modify(
            vertexHeaders[registry.at(handle).vertex_i], mesh.vertices,
            vertexFormat,
            vertexHeaders.getBuffer(),
            bindingPoint, 0,
            sizeof(geo::vertex));

        indexHeaders.modify(
            indexHeaders[registry.at(handle).index_i], mesh.indices,
            vertexFormat,
            indexHeaders.getBuffer());
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
}