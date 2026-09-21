#include "engine/scene/instances.hpp"

#include <glm/glm.hpp>
#include <tracy/Tracy.hpp>


namespace engine::scene {
    Instances::Instance Instances::operator[](std::size_t index) {
        return {
            positions[index],
            velocities[index],
            accelerations[index],
            forces[index],
            masses[index]
        };
    }

    void Instances::createInstance(Parameters param) {
        ZoneScoped;
        instanceCount++;

        positions.emplace_back(param.pos, 0);
        velocities.emplace_back(param.vel, 0);
        accelerations.emplace_back(param.accel, 0);
        forces.emplace_back(param.force, 0);
        masses.emplace_back(param.mass);
    }

    void Instances::clear() {
        instanceCount = 0;

        positions.clear();
        velocities.clear();
        accelerations.clear();
        forces.clear();
        masses.clear();
    }

    std::vector<glm::vec4>& Instances::instancesPos()  {return positions;}
    std::vector<glm::vec4>& Instances::instancesVel()  {return velocities;}
    std::vector<glm::vec4>& Instances::instancesAccel() {return accelerations;}
    std::vector<glm::vec4>& Instances::instancesForce() {return forces;}
    std::vector<float>& Instances::instancesMasses()  {return masses;}

    std::size_t Instances::size() const {return instanceCount;}
}