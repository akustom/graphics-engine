#pragma once

#include <vector>
#include <cassert>


namespace engine::core {
    struct rHandle {
        uint32_t sparse_index;
        uint32_t generation;
    };

    template <typename T>
    class registry {
    public:
        [[nodiscard]] const T& at(rHandle handle) const {
            auto [sparse_index, handle_gen] = handle;
            auto [dense_index, sparse_gen] = sparse[sparse_index];

            assert(handle_gen == sparse_gen && "Undefined handle used!");

            return dense[dense_index];
        }

        rHandle push(T data) {
            if (!free_list.empty()) {
                uint32_t free_id = free_list.back();
                free_list.pop_back();

                sparse[free_id].dense_index = dense.size();

                dense_to_sparse.push_back(free_id);
                dense.push_back(data);

                return rHandle{free_id, sparse[free_id].generation};
            }

            sparse.emplace_back(static_cast<uint32_t>(dense.size()), 0);

            dense_to_sparse.push_back(sparse.size() - 1);
            dense.push_back(data);

            return rHandle{static_cast<uint32_t>(sparse.size()) - 1, 0};
        }

        void free(rHandle handle) {
            auto& entry = sparse[handle.sparse_index];

            assert(handle.generation == entry.generation && "Undefined handle used!");

            ++entry.generation;

            if (entry.dense_index < dense.size() - 1) {
                modify_dense(entry.dense_index,
                dense_to_sparse.back(),
                dense.back());

                sparse[dense_to_sparse[entry.dense_index]].dense_index = entry.dense_index;
            }

            pop_dense();
            free_list.push_back(handle.sparse_index);
        }

        void modify(rHandle handle, T data) {
            auto& entry = sparse[handle.sparse_index];
            dense[entry.dense_index] = data;
        }

    private:
        struct SparseEntry {
            uint32_t dense_index;
            uint32_t generation;
        };

        std::vector<SparseEntry> sparse;
        std::vector<uint32_t> dense_to_sparse;
        std::vector<T> dense;

        std::vector<uint32_t> free_list;

        void pop_dense() {
            dense_to_sparse.pop_back();
            dense.pop_back();
        }

        void modify_dense(uint32_t dense_index, uint32_t to_sparse_i, T dense_data) {
            dense_to_sparse[dense_index] = to_sparse_i;
            dense[dense_index] = dense_data;
        }
    };
}