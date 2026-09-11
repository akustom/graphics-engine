#pragma once

#include <glm/fwd.hpp>

#include "glw/core/vao.hpp"
#include "glw/structure/vector.hpp"

#include "engine/core/registry.hpp"
#include "engine/geometry/vertex.hpp"

namespace engine::geo {
    struct Mesh;
}

namespace engine::gfx {
    class MeshBuffer {
    public:
        MeshBuffer(glw::VAO& vertex_format, unsigned int binding_point) :
            vertexFormat(vertex_format), bindingPoint(binding_point) {}
        const glw::HeaderPair<2>& operator[](core::Handle handle) const;

        core::Handle index(geo::Mesh& mesh);

    private:
        glw::VAO& vertexFormat;

        glw::vector<geo::vertex> vertexHeaders;
        glw::vector<glm::uint> indexHeaders;

        core::registry<glw::HeaderPair<2>> registry;

        unsigned int bindingPoint;

        void pushVertices(std::vector<geo::vertex>& vertices);
        void pushIndices(std::vector<glm::uint>& indices);
        void push(geo::Mesh& mesh);
    };
}
