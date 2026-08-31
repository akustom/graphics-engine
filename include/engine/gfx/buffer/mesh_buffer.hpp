#pragma once

#include "boost/unordered/unordered_flat_map.hpp"

#include "glw/core/vao.hpp"
#include "glw/structure/vector.hpp"

#include "engine/core/handle_issuer.hpp"
#include "engine/geometry/vertex.hpp"

namespace engine::geo {
    struct Mesh;
}

namespace engine::gfx {
    struct MeshBuffer {
        glw::VAO& vertexFormat;

        glw::vector<geo::vertex> vertexHeaders;
        glw::vector<glm::uint> indexHeaders;

        core::HandleIssuer issuer;

        boost::unordered_flat_map<core::Handle, glw::HeaderPair<2>> registry;

        int bindingPoint;

        MeshBuffer(glw::VAO& vertex_format, int binding_point) : vertexFormat(vertex_format), bindingPoint(binding_point) {}

        const glw::HeaderPair<2>& operator[](const core::Handle& handle) const;

        void pushVertices(std::vector<geo::vertex>& vertices);
        void pushIndices(std::vector<glm::uint>& indices);
        void push(geo::Mesh& mesh);

        const core::Handle& index(geo::Mesh& mesh);
    };
}
