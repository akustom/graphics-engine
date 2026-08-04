#pragma once

#include <vector>

#include "glm/glm.hpp"


namespace gfx {
    struct Mesh;
}


namespace engine {
    struct Instances {
        struct Instance {
            glm::vec4& position;
            glm::vec4& velocity;
            glm::vec4& acceleration;

            Instance(glm::vec4& pos, glm::vec4& vel, glm::vec4& accel) : position(pos), velocity(vel), acceleration(accel) {}
        };

        int instanceCount = 0;

        std::vector<glm::vec4> positions;
        std::vector<glm::vec4> velocities;
        std::vector<glm::vec4> accelerations;

        void createInstance(
            const glm::vec3& position = {0, 0, 0},
            const glm::vec3& velocity = {0, 0, 0},
            const glm::vec3& acceleration = {0, 0, 0}
            );

        Instance getInstance(size_t index) {
            return Instance{
                positions[index],
                velocities[index],
                accelerations[index]
            };
        }

    };
}