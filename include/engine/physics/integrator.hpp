#pragma once

#include <vector>
#include <algorithm>
#include <glm/vec4.hpp>
#include <tracy/Tracy.hpp>

#include "engine/scene/instances.hpp"


namespace engine::phy {
    struct VelocityVerlet {
        template <void(*...forces)(scene::Instances& instances)>
        static void apply_forces(scene::Instances& instances) {
            (forces(instances), ...);
        }

        static void clear_forces(scene::Instances& instances) {
            std::ranges::fill(instances.instancesForce(), glm::vec4(0));
        }

        template <void(*...forces)(scene::Instances& instances)>
        static void integrate(scene::Instances& instances, float dt) {
            ZoneScoped;

            for (int i = 0; i < instances.size(); i++) { // update pos -> x(t + dt)
                instances.instancesPos()[i] += instances.instancesVel()[i] * dt + 1.0f/2.0f * instances.instancesAccel()[i] * dt * dt;
            }

            for (int i = 0; i < instances.size(); i++) { // update vel -> v(t + dt/2)
                instances.instancesVel()[i] += 1.0f/2.0f * instances.instancesAccel()[i] * dt;
            }

            clear_forces(instances);
            apply_forces<forces...>(instances);
            for (int i = 0; i < instances.size(); i++) { // update accel -> a(t + dt)
                instances.instancesAccel()[i] = instances.instancesForce()[i]/instances.instancesMasses()[i];
            }

            for (int i = 0; i < instances.size(); i++) { // update vel -> v(t + dt)
                instances.instancesVel()[i] += 1.0f/2.0f * instances.instancesAccel()[i] * dt;
            }
        }
    };

    using VelVer = VelocityVerlet;
    using V_V = VelocityVerlet;
}