#include "engine/scene/instances.hpp"

#include <glm/glm.hpp>


namespace engine::scene {
    Instances::InstanceRef Instances::operator[](std::size_t index) {
        return InstanceRef{
            positions[index],
            velocities[index],
            accelerations[index]
        };
    }

    void Instances::createInstance(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& acceleration) {
        instanceCount++;

        positions.emplace_back(position, 0);
        velocities.emplace_back(velocity, 0);
        accelerations.emplace_back(acceleration, 0);
    }

    std::vector<glm::vec4>& Instances::instancesPos()  {return positions;}
    std::vector<glm::vec4>& Instances::instancesVel()  {return velocities;}
    std::vector<glm::vec4>& Instances::instancesAccel() {return accelerations;}

    std::size_t Instances::size() const {return instanceCount;}
}