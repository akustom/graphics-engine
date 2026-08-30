#pragma once

#include <vector>


namespace glw {
    struct IDAllocator {
        struct Handle {
            IDAllocator& parent;
            int id = -1;

            Handle(IDAllocator& parent_alloc, int id) : parent(parent_alloc), id(id) {}
            ~Handle() {parent.free(*this);}
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
            return Handle{*this, nextFreeHandle - 1};
        }
    };
}