#pragma once

#include "glw/buffer.hpp"
#include "glw/vao.hpp"

#include "engine/geometry/vertex.hpp"

namespace engine::geo {
    struct Mesh;
}

namespace engine::gfx {      // idea, find a way to delete meshes (current problems are indexing)
    struct MeshBuffer { // idea, after some time, if the buffer hasnt changed, i should make it so it turns from a dynamic one into a static one
        struct IndexData {
            int indexCount = 0;

            int ebo_offset;
            int vbo_offset;

            IndexData(const int index_count = 0, const int ebo_o = 0, const int vbo_o = 0) : indexCount(index_count), ebo_offset(ebo_o), vbo_offset(vbo_o) {}
        };

        struct BatchHeader {
            int size = 0;
            int capacity = 0;
        };

        std::vector<IndexData> indexedMeshes;

        glw::VAO& vertexFormat;

        glw::VBO vertexBuffer;
        glw::EBO indexBuffer;

        BatchHeader verticesBatchHeader;
        BatchHeader indicesBatchHeader;

        int bindingPoint;

        MeshBuffer(glw::VAO& vertex_format, int binding_point) : vertexFormat(vertex_format), bindingPoint(binding_point) {}

        IndexData getMeshOffset(geo::Mesh& mesh) const;

        void pushVertices(std::vector<geo::vertex>& vertices);
        void pushIndices(std::vector<glm::uint>& indices);
        void push(geo::Mesh& mesh);

        void index(geo::Mesh& mesh);

        glw::VAO& getVAO();
    };
}
