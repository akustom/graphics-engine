#pragma once

#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <boost/pfr.hpp>
#include <array>
#include <cstddef>


namespace util {
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
        size_t size = (... + source.size());
        dest.reserve(size);

        (moveVecHelper(dest, source), ...);
    }

    template <typename T>
    requires std::is_arithmetic_v<T>
    T random(T min, T max) {
        static std::random_device rd;
        std::uniform_real_distribution dis(min, max);
        return dis(rd);
    }

    template <typename... T>
    void print(const T&... data) {
        ((std::cout << data), ...) << '\n';
    }

    template <typename T, std::size_t I>
    std::size_t getOffset() {
        const T dummy{};

        const auto* field =
            reinterpret_cast<const std::byte*>(
                std::addressof(boost::pfr::get<I>(dummy))
            );

        const auto* base = reinterpret_cast<const std::byte*>(std::addressof(dummy));

        return static_cast<std::size_t>(field - base);
    }

    template <typename T, std::size_t... I>
    constexpr auto getOffsetsImpl(std::index_sequence<I...>) {
        return std::array<std::size_t, sizeof...(I)>{
            getOffset<T, I>()...
        };
    }

    template <typename T>
    constexpr auto getOffsets() {
        constexpr std::size_t N = boost::pfr::tuple_size_v<T>;
        return getOffsetsImpl<T>(std::make_index_sequence<N>{});
    }

    template <typename T, std::size_t... I>
    constexpr auto getSizesImpl(std::index_sequence<I...>) {
        return std::array<std::size_t, sizeof...(I)>{
            sizeof(boost::pfr::tuple_element_t<I, T>)...
        };
    }

    template <typename T>
    constexpr auto getSizes() {
        constexpr std::size_t N = boost::pfr::tuple_size_v<T>;
        return getSizesImpl<T>(std::make_index_sequence<N>{});
    }
}