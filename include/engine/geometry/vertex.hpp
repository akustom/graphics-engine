#pragma once

#include <glm/vec3.hpp>


namespace engine::geo {
    struct vertex {
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec3 normal;

        vertex(
            glm::vec3 pos = glm::vec3(0),
            glm::vec3 color = glm::vec3(0),
            glm::vec3 normal = glm::vec3(0))
        : pos(pos), color(color), normal(normal) {}
    };
}