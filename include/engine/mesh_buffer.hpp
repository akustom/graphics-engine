#pragma once

#include "glw/buffer.hpp"
#include "glw/vao.hpp"

#include "gfx/vertex.hpp"
#include "gfx/mesh.hpp"


namespace engine {
    struct MeshBuffer {
        struct IndexData {
            int indexCount = 0;

            int ebo_offset;
            int vbo_offset;

            IndexData(const int ebo_o = 0, const int vbo_o = 0) : ebo_offset(ebo_o), vbo_offset(vbo_o) {}
        };

        struct BatchStorageData {
            int size = 0;
            int capacity = 0;
        };

        glw::VBO vertexBuffer;
        glw::EBO indexBuffer;
        glw::VAO vertexFormat;

        MeshBuffer() { // TODO: refactor this to be more flexible with its formatting (use boost)
            vertexFormat.formatAttribute(0, 0, 3, GL_FLOAT, offsetof(gfx::vertex, pos));
            vertexFormat.formatAttribute(1, 0, 3, GL_FLOAT, offsetof(gfx::vertex, color));
            vertexFormat.formatAttribute(2, 0, 3, GL_FLOAT, offsetof(gfx::vertex, normal));

            vertexFormat.formatAttribute(3, 1, 4, GL_FLOAT, 0);
            vertexFormat.setAttributeDivisor(1, 1);
        }

        std::vector<IndexData> indexedMeshes;

        BatchStorageData verticesBatchData;
        BatchStorageData indicesBatchData;

        IndexData getMeshOffset(gfx::Mesh& mesh) const;
        void addMesh(gfx::Mesh& mesh);
        void indexMesh(gfx::Mesh& mesh);

        glw::VAO& getVAO();
    };
}
