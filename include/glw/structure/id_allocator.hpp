#pragma once

#include <vector>


namespace glw {
    struct IDAllocator {
        struct Handle {
            IDAllocator* parent;
            int id = -1;

            Handle(IDAllocator& parent_alloc, int id) : parent(&parent_alloc), id(id) {}
            ~Handle() {parent->free(*this);}

            Handle(const Handle&) = delete;
            Handle& operator=(const Handle&) = delete;

            Handle(Handle&& other) noexcept : parent(other.parent), id(other.id) {
                other.id = -1;
            }

            Handle& operator=(Handle&& other) noexcept {
                if (this != &other) {
                    std::swap(parent, other.parent);
                    std::swap(id, other.id);
                }
                return *this;
            }
        };


        std::vector<int> oldFreeHandles;
        int nextFreeHandle = 0;

        void free(const Handle& handle) {
            if (handle.id == -1)
                return;

            oldFreeHandles.push_back(handle.id);
        }

        Handle getUniqueHandle() {
            if (!oldFreeHandles.empty()) {
                int id = oldFreeHandles.back();
                oldFreeHandles.pop_back();

                return Handle{*this, id};
            }

            nextFreeHandle++;
            return Handle{*this, nextFreeHandle--};
        }
    };
}