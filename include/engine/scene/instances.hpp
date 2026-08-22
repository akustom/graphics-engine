#pragma once

#include <vector>

#include <glm/glm.hpp>


namespace engine::scene {
    struct Instances {
        struct InstanceRef {
            glm::vec4& position;
            glm::vec4& velocity;
            glm::vec4& acceleration;

            InstanceRef(glm::vec4& pos, glm::vec4& vel, glm::vec4& accel) : position(pos), velocity(vel), acceleration(accel) {}
        };

        std::vector<glm::vec4> positions;

        std::vector<glm::vec4> velocities;
        std::vector<glm::vec4> accelerations;

        int instanceCount = 0;

        int id = -1;

        InstanceRef operator[](size_t index) { // getting an instance
            return InstanceRef{
                positions[index],
                velocities[index],
                accelerations[index]
            };
        }

        void createInstance(
            const glm::vec3& position = {0, 0, 0},
            const glm::vec3& velocity = {0, 0, 0},
            const glm::vec3& acceleration = {0, 0, 0}
            );
    };
}