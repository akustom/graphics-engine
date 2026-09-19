#pragma once

#include <vector>

#include "glw/core/vao.hpp"
#include "glw/core/buffer.hpp"


namespace glw {
    struct IndexHeader {
        uint32_t count;
        uint32_t bufferOffset;

        IndexHeader(uint32_t count, uint32_t buffer_offset) : count(count), bufferOffset(buffer_offset) {}
    };

    template <uint32_t size>
    using HeaderPair = std::array<IndexHeader, size>;


    template <typename T>
    struct vector {
        std::vector<IndexHeader> indexed;
        Buffer buffer;
        std::size_t item_size     = 0;
        std::size_t item_capacity = 0;

        [[nodiscard]] std::size_t size() const {
            return indexed.size();
        }

        IndexHeader operator[](std::size_t i) const {
            return indexed[i];
        }

        IndexHeader back() {
            return indexed.back();
        }

        Buffer& getBuffer() {
            return buffer;
        }

        void reserve(std::size_t capacity) {
            this->item_capacity = capacity;

            Buffer temp;

            temp.allocateBuffer<T>(capacity, GL_DYNAMIC_STORAGE_BIT);
            temp.copyData<T>(buffer, item_size);

            buffer = std::move(temp);
        }

        template <typename... Args>
        void buffer_push(std::vector<T>& obj, VAO& format, Args&&... args) {
            if (item_size == 0) {
                item_capacity = obj.size();
                buffer.allocateBuffer(obj, GL_DYNAMIC_STORAGE_BIT);
                format.attachBuffer(buffer, std::forward<Args>(args)...);
            } else {
                if (item_size + obj.size() > item_capacity) {
                    reserve(2 * std::max(item_size, obj.size()));
                    format.attachBuffer(buffer, std::forward<Args>(args)...);
                }
                buffer.pushData(sizeof(T) * item_size, obj);
            }
        }

        template <typename... Args>
        void push_back(std::vector<T>& obj, VAO& format, Args&&... args) {
            buffer_push(obj, format, std::forward<Args>(args)...);

            indexed.emplace_back(
                static_cast<uint32_t>(obj.size()),
                static_cast<uint32_t>(item_size));
            item_size += obj.size();
        }

        template <typename... Args>
        void modify(IndexHeader header, std::vector<T>& obj, VAO& format, Args&&... args) {
            if (header.count != static_cast<uint32_t>(obj.size())) {
                int32_t buffer_diff = static_cast<uint32_t>(obj.size()) - header.count;

                uint32_t old_end = header.bufferOffset + header.count;
                uint32_t tail_count = static_cast<int>(item_size) - old_end;
                uint32_t new_offset = header.bufferOffset + static_cast<int>(obj.size());

                if (item_size + buffer_diff > item_capacity) {
                    reserve(2 * (item_size + buffer_diff));
                    format.attachBuffer(buffer, std::forward<Args>(args)...);
                }

                if (tail_count > 0) {
                    Buffer temp;
                    temp.allocateBuffer<T>(tail_count, GL_DYNAMIC_STORAGE_BIT);
                    temp.copyData<T>(buffer, tail_count, old_end, 0);
                    buffer.copyData<T>(temp, tail_count, 0, new_offset);
                }

                item_size += buffer_diff;

                for (auto& idxH : indexed) {
                    if (idxH.bufferOffset == header.bufferOffset)
                        idxH.count = static_cast<uint32_t>(obj.size());

                    if (idxH.bufferOffset > header.bufferOffset)
                        idxH.bufferOffset += buffer_diff;
                }
            }

            buffer.pushData(sizeof(T) * header.bufferOffset, obj);
        }
    };
}