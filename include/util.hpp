#pragma once

#include <algorithm>
#include <vector>


template <typename T>
size_t bytesof(const std::vector<T>& vec) {
    return vec.size() * sizeof(T);
}
template <typename T>
constexpr size_t bytesof() {
    return sizeof(T);
}

template <typename T>
void moveVecHelper(std::vector<T>& dest, std::vector<T>& source) {
    dest.insert(
    dest.end(),
    std::make_move_iterator(source.begin()),
    std::make_move_iterator(source.end()));

    source.clear();
}

template <typename T, typename... Args>
void moveVec(std::vector<T>& dest, Args&... source) {
    size_t size = (source.size() + ...);
    dest.reserve(size);

    (moveVecHelper(dest, source), ...);
}

template <typename T, typename Y>
constexpr int sc(Y arg) {
    return static_cast<T>(arg);
}