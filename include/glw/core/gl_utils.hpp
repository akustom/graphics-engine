#pragma once

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/fwd.hpp>


template <typename T>
    concept trivially_copyable = std::is_trivially_copyable_v<T>;

template<typename T>
constexpr auto getPtr(const T& data) {
    if constexpr (std::is_same_v<T,glm::mat4>)
        return glm::value_ptr(data);
    else static_assert("uniform type is currently unsupported\n");
}

template <typename T>
constexpr int TypeToMac = []{
        if constexpr (std::is_same_v<T, glm::uint16_t>)
            return GL_UNSIGNED_SHORT;
        else if constexpr (std::is_same_v<T, glm::uint32_t> || std::is_same_v<T, glm::uint>)
            return GL_UNSIGNED_INT;
        else static_assert("unknown type\n");
}();