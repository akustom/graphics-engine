#pragma once

#include <vector>

#include "glw/primitive/buffer.hpp"
#include "util.hpp"


namespace glw {
    template <typename T>
    struct vector {
        struct IndexHeader {
            int count;
            int bufferOffset;

            IndexHeader(int count, int buffer_offset) : count(count), bufferOffset(buffer_offset) {}
        };

        std::vector<IndexHeader> indexed;

        int size = 0;
        int capacity = 0;

        Buffer buffer;

        Buffer& getBuffer() {
            return buffer;
        }

        IndexHeader operator[](int i) const {
            return indexed[i];
        }

        void reserve(int capacity) {
            this->capacity = capacity;

            Buffer temp;

            temp.allocateBuffer<T>(capacity, GL_DYNAMIC_STORAGE_BIT);
            temp.copyData<T>(buffer, size);

            buffer = std::move(temp);
        }

        template <typename... Args>
        void push_buffer(std::vector<T>& obj, VAO& format, Args&&... args) {
            if (size == 0) {
                capacity = obj.size();
                buffer.allocateBuffer(obj);
                format.attachBuffer(std::forward<Args>(args)...);
            }
            else {
                if (size + obj.size() > capacity) {
                    reserve(2 * std::max(size, static_cast<int>(obj.size())));
                    format.attachBuffer(std::forward<Args>(args)...);
                }
                buffer.pushData(static_cast<int>(util::bytesof<T>()) * size, obj);
            }
        }

        template <typename... Args>
        int push_back(std::vector<T>& obj, VAO& format, Args&&... args) {
            push_buffer(obj, format, std::forward<Args>(args)...);

            indexed.emplace_back(obj.size(), size);
            size += obj.size();

            return indexed.size() - 1;
        }
    };
}