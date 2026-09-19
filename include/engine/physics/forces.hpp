#pragma once

#include <glm/vec4.hpp>
#include <glm/geometric.hpp>

#include "engine/scene/instances.hpp"

namespace engine::phy {
    inline glm::vec4 gravity(const scene::Instances::Instance& instance, const scene::Instances::Instance& other) {
        float G = 0.0000000000667430f;

        glm::vec4 dist = other.position - instance.position;
        float diff = glm::length(dist);

        glm::vec4 force = (diff >= 0.1) ?
            G * (instance.mass * other.mass / (diff*diff)) * glm::normalize(dist) : glm::vec4(0);

        return force;
    }

    inline glm::vec4 custom_force(const scene::Instances::Instance& instance, const scene::Instances::Instance& other) {
        glm::vec3 pos_a = glm::vec3(instance.position);
        glm::vec3 pos_b = glm::vec3(other.position);

        glm::vec3 delta = pos_a - pos_b;
        float dist = glm::length(delta);

        constexpr float max_radius = 8.0f;

        // FIX 1: Ignore anything outside max radius completely
        if (dist > max_radius || dist < 0.01f) {
            return glm::vec4(0.0f);
        }

        glm::vec3 radial_dir = delta / dist;
        glm::vec3 up_axis = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 tangent_dir = glm::cross(up_axis, radial_dir);

        // Re-normalize tangent to handle floating point edge cases
        if (glm::dot(tangent_dir, tangent_dir) > 0.0001f) {
            tangent_dir = glm::normalize(tangent_dir);
        } else {
            tangent_dir = glm::vec3(0.0f);
        }

        // Smooth falloff: strong near core, zero at max_radius
        float norm_dist = dist / max_radius;
        float falloff = (1.0f - norm_dist) * (1.0f - norm_dist);

        constexpr float swirl_strength = 8.0f; // Orbital force
        constexpr float inward_pull   = 3.0f; // Pulls particles toward center so they orbit

        glm::vec3 force = (tangent_dir * swirl_strength - radial_dir * inward_pull) * falloff;

        // FIX 2: Velocity dampening so particles don't gain infinite speed
        glm::vec3 vel_a = glm::vec3(instance.velocity);
        force -= vel_a * 0.1f;

        return glm::vec4(force, 0.0f);
    }
}