#pragma once

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/fwd.hpp>


template <typename T>
    concept trivially_copyable = std::is_trivially_copyable_v<T>;

template <typename T>
constexpr int GL_MACRO = []{
    if constexpr (std::is_same_v<T, glm::uint16_t>)
        return GL_UNSIGNED_SHORT;
    else if constexpr (std::is_same_v<T, glm::uint32_t> || std::is_same_v<T, glm::uint>)
        return GL_UNSIGNED_INT;
    else static_assert("unknown type\n");
}();