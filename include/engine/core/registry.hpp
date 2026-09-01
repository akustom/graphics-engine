#pragma once

#include <vector>


namespace engine::core {
    struct rHandle {
        int id;
        int gen;
    };

    struct Registry {
        struct SparseEntry {
            int denseIndex;
            int generation;
        };

        std::vector<SparseEntry> sparse;
        std::vector<int> dense;

        std::vector<int> free_list;

        int at(rHandle handle) {
            auto [handleID, handleGen] = handle;
            auto [denseIndex, sparseGen] = sparse[handleID];

            if (handleGen != denseIndex) {

            }

            return dense[denseIndex];
        }

        rHandle create() {
            if (!free_list.empty()) {
                int free_id = free_list.back();
                free_list.pop_back();

                return rHandle{free_id, sparse[free_id].generation};
            }

            sparse.emplace_back(dense.size(), 0);
            return rHandle{static_cast<int>(sparse.size()) - 1, 0};
        }

        void free(rHandle handle) {
            auto [handleID, handleGen] = handle;
            auto& [denseIndex, sparseGen] = sparse[handleID];

            dense.erase(dense.begin() + denseIndex);

        }

        void modify(rHandle handle, const int& data) {
            auto& [denseIndex, sparseGen] = sparse[handle.id];
                sparseGen++;

            int& denseData = dense[denseIndex];
                denseData = data;
        }
    };
}