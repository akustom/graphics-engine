#pragma once

#include <vector>


namespace engine::core {
    struct HandleIssuer {
        struct Handle {
            HandleIssuer* parent;
            int id = -1;

            Handle(HandleIssuer& parent_alloc, int id);
            ~Handle();

            Handle(const Handle&) = delete;
            Handle& operator=(const Handle&) = delete;

            Handle(Handle&& other) noexcept;

            Handle& operator=(Handle&& other) noexcept;
        };


        std::vector<int> oldFreeHandles;
        int nextFreeHandle = 0;

        void free(const Handle& handle);

        Handle getUniqueHandle();
    };

    using Handle = HandleIssuer::Handle;
}