#pragma once

#include <vector>

#include <glm/glm.hpp>


namespace engine::scene {
    class Instances {
    public:
        struct InstanceRef {
            glm::vec4& position;
            glm::vec4& velocity;
            glm::vec4& acceleration;

            InstanceRef(glm::vec4& pos, glm::vec4& vel, glm::vec4& accel) : position(pos), velocity(vel), acceleration(accel) {}
        };

        InstanceRef operator[](std::size_t index); // getting an instance

        void createInstance(
            const glm::vec3& position = {0, 0, 0},
            const glm::vec3& velocity = {0, 0, 0},
            const glm::vec3& acceleration = {0, 0, 0}
            );

        std::vector<glm::vec4>& instancesPos();
        std::vector<glm::vec4>& instancesVel();
        std::vector<glm::vec4>& instancesAccel();

        std::size_t size() const;

    private:
        std::vector<glm::vec4> positions;

        std::vector<glm::vec4> velocities;
        std::vector<glm::vec4> accelerations;

        std::size_t instanceCount = 0;
    };
}