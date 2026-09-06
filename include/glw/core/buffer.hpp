#pragma once

#include <vector>
#include <glad/glad.h>
#include "gl_utils.hpp"
#include "util.hpp"


namespace glw {
    struct Buffer {
        GLuint id = 0;

        void create() {
            glCreateBuffers(1, &id);
        }
        void destroy() {
            glDeleteBuffers(1, &id);
            id = 0;
        }

        Buffer() {
            create();
        }

        ~Buffer() {
            destroy();
        }
        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;

        Buffer(Buffer&& other) noexcept {
            this->id = other.id;
            other.id = 0;
        }
        Buffer& operator=(Buffer&& other) noexcept {
            if (this != &other) {
                glDeleteBuffers(1, &id);

                this->id = other.id;
                other.id = 0;
            }
            return *this;
        }

        template <trivially_copyable T>
        void allocateBuffer(std::vector<T>& init_data, const GLenum flag = 0) const {
            glNamedBufferStorage(id, util::sizeof_v(init_data), init_data.data(), flag);
        }

        template <trivially_copyable T>
        void allocateBuffer(std::size_t size, const GLenum flag = 0) const {
            glNamedBufferStorage(id, sizeof(T) * size, nullptr, flag);
        }

        template <trivially_copyable T>
        void pushData(const std::size_t byte_offset, std::vector<T>& data) const {
            glNamedBufferSubData(id, byte_offset, util::sizeof_v(data), data.data());
        }
        template <trivially_copyable T>
        void pushData(const std::size_t byte_offset, T& data) const {
            glNamedBufferSubData(id, byte_offset, sizeof(T), glm::value_ptr(data));
        }

        template <trivially_copyable T>
        void copyData(Buffer& srcBuffer, std::size_t size) const {
            glCopyNamedBufferSubData(srcBuffer.id, id, 0, 0, size * sizeof(T));
        }
    };

    struct UBO : Buffer {
        void bind(const GLuint binding_loc) const {
            glBindBufferBase(GL_UNIFORM_BUFFER, binding_loc, id);
        }

        void allocateBuffer(const std::size_t byte_offset) const {
            glNamedBufferStorage(id, byte_offset, nullptr, GL_DYNAMIC_STORAGE_BIT);
        }

        template <trivially_copyable D>
        void pushUniform(const std::size_t byte_offset, const D& data) const {
            this->pushData(byte_offset, data);
        }
    };

    using VBO = Buffer;
    using EBO = Buffer;
}
