#pragma once

#include <vector>


namespace engine::core {
    struct HandleIssuer {
        struct Handle {
            HandleIssuer* parent = nullptr;
            int id = -1;

            Handle(HandleIssuer* parent_alloc, int id);
            ~Handle();

            Handle(const Handle&) = delete;
            Handle& operator=(const Handle&) = delete;

            Handle(Handle&& other) noexcept;

            Handle& operator=(Handle&& other) noexcept;

            bool operator==(const Handle& other) const;

            friend std::size_t hash_value(const Handle& p);
        };


        std::vector<int> oldFreeHandles;
        int nextFreeHandle = 0;

        void free(const Handle& handle);

        Handle getUnique();

    };

    using Handle = HandleIssuer::Handle;
}