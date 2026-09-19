#pragma once

#include <vector>
#include <algorithm>
#include <glm/vec4.hpp>
#include <tracy/Tracy.hpp>

#include "engine/scene/instances.hpp"


namespace engine::phy {
    struct VelocityVerlet {
        template <glm::vec4(*...forces)(const scene::Instances::Instance&, const scene::Instances::Instance&)>
        static void apply_forces(scene::Instances& instances) {
            auto* force_loc = instances.instancesForce().data();
            for (int i = 0; i < instances.size(); i++) {
                for (int j = i+1; j < instances.size(); j++) {
                    glm::vec4 force = (glm::vec4(0) + ... + forces(instances[i],instances[j]));

                    force_loc[i] += force;
                    force_loc[j] -= force;
                }
            }
        }

        static void clear_forces(scene::Instances& instances) {
            std::ranges::fill(instances.instancesForce(), glm::vec4(0));
        }

        template <glm::vec4(*...forces)(const scene::Instances::Instance&, const scene::Instances::Instance&)>
        static void integrate(scene::Instances& instances, float dt) {
            ZoneScoped;

            for (int i = 0; i < instances.size(); i++) { // update pos -> x(t + dt)
                instances.instancesPos()[i] += instances.instancesVel()[i] * dt + 1.0f/2.0f * instances.instancesAccel()[i] * dt * dt;
            }

            for (int i = 0; i < instances.size(); i++) { // update vel -> v(t + dt/2)
                instances.instancesVel()[i] += 1.0f/2.0f * instances.instancesAccel()[i] * dt;
            }

            apply_forces<forces...>(instances);
            for (int i = 0; i < instances.size(); i++) { // update accel -> a(t + dt)
                instances.instancesAccel()[i] += instances.instancesForce()[i]/instances.instancesMasses()[i];
            }
            clear_forces(instances);

            for (int i = 0; i < instances.size(); i++) { // update vel -> v(t + dt)
                instances.instancesVel()[i] += 1.0f/2.0f * instances.instancesAccel()[i] * dt;
            }
        }
    };

    using VelVer = VelocityVerlet;
    using V_V = VelocityVerlet;
}