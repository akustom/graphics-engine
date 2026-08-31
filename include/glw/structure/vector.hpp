#pragma once

#include <vector>

#include "glw/core/buffer.hpp"


namespace glw {
    template <typename T>
    struct vector {
        struct IndexHeader {
            int count;
            int bufferOffset;

            IndexHeader(int count, int buffer_offset) : count(count), bufferOffset(buffer_offset) {}
        };


        std::vector<IndexHeader> indexed;
        Buffer buffer;
        int size     = 0;
        int capacity = 0;


        IndexHeader operator[](int i) const {
            return indexed[i];
        }

        Buffer& getBuffer() {
            return buffer;
        }

        void reserve(int capacity) {
            this->capacity = capacity;

            Buffer temp;

            temp.allocateBuffer<T>(capacity, GL_DYNAMIC_STORAGE_BIT);
            temp.copyData<T>(buffer, size);

            buffer = std::move(temp);
        }

        template <typename... Args>
        void buffer_push(std::vector<T>& obj, VAO& format, Args&&... args) {
            if (size == 0) {
                capacity = obj.size();
                buffer.allocateBuffer(obj);
                format.attachBuffer(std::forward<Args>(args)...);
            } else {
                if (size + obj.size() > capacity) {
                    reserve(2 * std::max(size, static_cast<int>(obj.size())));
                    format.attachBuffer(std::forward<Args>(args)...);
                }
                buffer.pushData(sizeof(T) * size, obj);
            }
        }

        template <typename... Args>
        int push_back(std::vector<T>& obj, VAO& format, Args&&... args) {
            buffer_push(obj, format, std::forward<Args>(args)...);

            indexed.emplace_back(obj.size(), size);
            size += obj.size();

            return indexed.size() - 1;
        }
    };
}