#pragma once

#include <vector>
#include <glad/glad.h>
#include "gl_utils.hpp"
#include "glw/primitive/buffer.hpp"


namespace glw {
    class VAO {
        GLuint id = 0;

        void gen() {
            glCreateVertexArrays(1, &id);
        }

    public:
        VAO() {
            gen();
        }
        ~VAO() {
            glDeleteVertexArrays(1, &id);
        }
        VAO(const VAO&) = delete;
        VAO& operator=(const VAO&) = delete;

        VAO(VAO&& other) noexcept {
            this->id = other.id;
            other.id = 0;
        }
        VAO& operator=(VAO&& other) noexcept {
            if (this != &other) {
                glDeleteVertexArrays(1, &id);

                id = other.id;
                other.id = 0;
            }
            return *this;
        }

        void bind() const {
            glBindVertexArray(id);
        }

        /**use offsetof(struct, member) to calculate byte_offset*/
        void formatAttribute(const int attrib_loc, const int binding_point, const int size, const GLenum type, const int byte_offset) const {
            glEnableVertexArrayAttrib(id, attrib_loc);
            glVertexArrayAttribFormat(id, attrib_loc, size, type, GL_FALSE, byte_offset);
            glVertexArrayAttribBinding(id, attrib_loc, binding_point);
        }

        template <typename T, typename Y>
        void formatAttribute(int start_attrib_loc, int binding_point, GLenum type) {
            auto vertexMemberSizes = util::getSizes<T>();
            auto vertexOffsets = util::getOffsets<T>();
            for (int i = 0; i < vertexOffsets.size(); i++)
                formatAttribute(start_attrib_loc + i, binding_point, vertexMemberSizes[i] / sizeof(Y), type, vertexOffsets[i]);
        }

        void setAttributeDivisor(const int binding_point, const int divisor) const {
            glVertexArrayBindingDivisor(id, binding_point, divisor);
        }

        /**use offsetof(struct, member) to calculate byte_offset,*/
        void attachBuffer(const VBO& vbo, const int binding_point, const int byte_offset, const int byte_stride) const {
            glVertexArrayVertexBuffer(id, binding_point, vbo.id, byte_offset, byte_stride);
        }
        void attachBuffer(const EBO& ebo) const {
            glVertexArrayElementBuffer(id, ebo.id);
        }
    };
}