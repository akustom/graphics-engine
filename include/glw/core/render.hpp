#pragma once

#include <glad/glad.h>


namespace glw {
    inline void drawInstances(unsigned int instance_count, unsigned int indices_count) {
        glDrawElementsInstanced(
        GL_TRIANGLES,
        indices_count,
        GL_UNSIGNED_INT,
        nullptr,
        instance_count);
    }

    inline void drawInstancesBaseVertex(const unsigned int instance_count, const unsigned int indices_count, const unsigned int ebo_offset, const unsigned int vbo_offset) {
        glDrawElementsInstancedBaseVertex(
        GL_TRIANGLES,
        indices_count,
        GL_UNSIGNED_INT,
        reinterpret_cast<void*>(ebo_offset * sizeof(unsigned int)),
        instance_count,
        vbo_offset);
    }

    inline void drawInstancesBaseVertexBaseInstances(const unsigned int instance_count, const unsigned int indices_count, const unsigned int ebo_offset, const unsigned int vbo_offset, const unsigned int instance_offset) {
        glDrawElementsInstancedBaseVertexBaseInstance(
            GL_TRIANGLES,
            indices_count,
            GL_UNSIGNED_INT,
            reinterpret_cast<void*>(ebo_offset * sizeof(unsigned int)),
            instance_count,
            vbo_offset,
            instance_offset);
    }
}

