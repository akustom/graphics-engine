#pragma once

#include "glw/buffer.hpp"
#include "glw/vao.hpp"

#include "gfx/vertex.hpp"

namespace gfx {
    struct Mesh;
}


namespace engine {      // idea, find a way to delete meshes (current problems are indexing)
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

        int bindingLocation;

        MeshBuffer(glw::VAO& vertex_format, int binding_loc) : vertexFormat(vertex_format), bindingLocation(binding_loc) { // TODO: refactor this to be more flexible with its formatting (use boost)
            vertexFormat.formatAttribute(0, binding_loc, 3, GL_FLOAT, offsetof(gfx::vertex, pos));
            vertexFormat.formatAttribute(1, binding_loc, 3, GL_FLOAT, offsetof(gfx::vertex, color));
            vertexFormat.formatAttribute(2, binding_loc, 3, GL_FLOAT, offsetof(gfx::vertex, normal));

            vertexFormat.formatAttribute(3, 1, 4, GL_FLOAT, 0);
            vertexFormat.setAttributeDivisor(1, 1);
        }

        IndexData getMeshOffset(gfx::Mesh& mesh) const;

        void pushVertices(std::vector<gfx::vertex>& vertices);
        void pushIndices(std::vector<glm::uint>& indices);
        void push(gfx::Mesh& mesh);

        void indexMesh(gfx::Mesh& mesh);

        glw::VAO& getVAO();
    };
}
