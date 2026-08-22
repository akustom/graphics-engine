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

        glw::vector<geo::vertex> vertexHandles;
        glw::vector<glm::uint> indexHandles;

        int bindingPoint;
        int nextFreeIndex = 0;

        MeshBuffer(glw::VAO& vertex_format, int binding_point) : vertexFormat(vertex_format), bindingPoint(binding_point) {}

        void pushVertices(std::vector<geo::vertex>& vertices);
        void pushIndices(std::vector<glm::uint>& indices);
        void push(geo::Mesh& mesh);

        void index(geo::Mesh& mesh);
    };
}
