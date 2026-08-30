#pragma once

#include "glw/primitive/vao.hpp"
#include "glw/structure/vector.hpp"

#include "engine/geometry/vertex.hpp"

namespace engine::geo {
    struct Mesh;
}

namespace engine::gfx {
    struct MeshBuffer {
        glw::VAO& vertexFormat;

        glw::vector<geo::vertex> vertexHeaders;
        glw::vector<glm::uint> indexHeaders;

        int bindingPoint;
        int nextFreeIndex = 0;

        MeshBuffer(glw::VAO& vertex_format, int binding_point) : vertexFormat(vertex_format), bindingPoint(binding_point) {}

        int pushVertices(std::vector<geo::vertex>& vertices);
        int pushIndices(std::vector<glm::uint>& indices);
        int push(geo::Mesh& mesh);

        int index(geo::Mesh& mesh);
    };
}
