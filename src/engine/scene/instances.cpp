#include "engine/scene/instances.hpp"

#include "glm/glm.hpp"


namespace engine::scene {
    void Instances::createInstance(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& acceleration) {
        instanceCount++;

        positions.emplace_back(position, 0);
        velocities.emplace_back(velocity, 0);
        accelerations.emplace_back(acceleration, 0);
    }
}