#pragma once

#include <vector>


namespace engine::core {
    struct rHandle {
        int sparse_index;
        int generation;
    };

    struct Registry {
        struct SparseEntry {
            int dense_index;
            int generation;
        };

        std::vector<SparseEntry> sparse;
        std::vector<int> dense;
        std::vector<int> dense_tsp;

        std::vector<int> free_list;

        void push_dense(int sparse_index, const int& data) {
            dense_tsp.push_back(sparse_index);
            dense.push_back(data);
        }

        void pop_dense() {
            dense_tsp.pop_back();
            dense.pop_back();
        }

        void modify_dense(int dense_index, int tsp_sparse_i, const int& dense_data) {
            dense_tsp[dense_index] = tsp_sparse_i;
            dense[dense_index] = dense_data;
        }

        [[nodiscard]] int at(rHandle handle) const {
            auto [sparse_index, handle_gen] = handle;
            auto [dense_index, sparse_gen] = sparse[sparse_index];

            assert(handle_gen == sparse_gen && "Undefined handle used!"); // todo to be refactored off in future debug class

            return dense[dense_index];
        }

        rHandle create(int data) {
            if (!free_list.empty()) {
                int free_id = free_list.back();
                free_list.pop_back();

                sparse[free_id].dense_index = static_cast<int>(dense.size());

                dense_tsp.push_back(free_id);
                dense.push_back(data);

                return rHandle{free_id, sparse[free_id].generation};
            }

            sparse.emplace_back(dense.size(), 0);

            dense_tsp.push_back(static_cast<int>(sparse.size()) - 1);
            dense.push_back(data);

            return rHandle{static_cast<int>(sparse.size()) - 1, 0};
        }

        void free(rHandle handle) {
            auto& entry = sparse[handle.sparse_index];
            entry.generation++;

            modify_dense(entry.dense_index,
                dense_tsp.back(),
                dense.back());
            pop_dense();

            sparse[dense_tsp[entry.dense_index]].dense_index = entry.dense_index;

            free_list.push_back(handle.sparse_index);
        }

        void modify(rHandle handle, const int& data) {

        }
    };
}