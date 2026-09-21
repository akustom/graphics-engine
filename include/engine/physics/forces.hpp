#pragma once

#include <glm/vec4.hpp>
#include <glm/geometric.hpp>

#include "engine/core/simd/s_vec4.hpp"
#include "engine/scene/instances.hpp"


namespace engine::phy {
    inline void gravity(scene::Instances& instances) {
        ZoneScoped;
        static constexpr float G = 0.0000000000667430f;

        __m256 m256_g_constant = _mm256_set1_ps(G);

        const std::size_t items = instances.size();
        const std::size_t tail  = items - items % simd::OFFSET_256::vec4;

        for (int i = 0; i < items; i++) {
            glm::vec4 self_pos = instances[i].position;
            glm::vec4 self_force = instances[i].force;
            float self_mass = instances[i].mass;

            __m256 m256_self_pos  = simd::_mm256_set1_vec4(self_pos);
            __m256 m256_self_mass = simd::_mm256_set1_vec4(self_mass);

            for (std::size_t j = 0; j < tail; j += simd::OFFSET_256::vec4) {
                __m256 m256_other_pos   = simd::_mm256_loadu_vec4(&instances.instancesPos()[j]);
                __m256 m256_other_force = simd::_mm256_loadu_vec4(&instances.instancesForce()[j]);
                __m256 m256_other_mass = simd::_mm256_alignf_vec4(
                    instances.instancesMasses()[j],
                    instances.instancesMasses()[j+1]);

                __m256 m256_diff = simd::_mm256_sub_vec4(m256_self_pos, m256_other_pos); // self_pos - other_pos
                __m256 m256_dir  = simd::_mm256_norm_vec4(m256_diff); // norm(self_pos - other_pos)

                __m256 m256_denom = simd::_mm256_length2_vec4(m256_diff); // mag(self_pos - other_pos)^2

                __m256 m256_numer = simd::_mm256_mul_vec4(m256_dir, m256_other_mass); // dir * m1
                m256_numer = simd::_mm256_mul_vec4(m256_numer, m256_self_mass); // dir * m1 * m2
                m256_numer = simd::_mm256_mul_vec4(m256_numer, m256_g_constant); // dir * m1 * m2 * G

                __m256 m256_force = simd::_mm256_div_vec4(m256_numer, m256_denom); // dir * m1 * m2 * G / mag^2
                m256_force = simd::_mm256_add_vec4(m256_other_force, m256_force);

                simd::_mm256_storeu_vec4(&instances.instancesForce()[j], m256_force);
            }

            for (std::size_t j = tail; j < items; j++) {
                glm::vec4 dist = instances[i].position - instances[j].position;
                float diff = glm::length(dist);

                glm::vec4 force = (diff >= 0.1) ?
                    G * (instances[i].mass * instances[j].mass / (diff*diff)) * glm::normalize(dist) :
                    glm::vec4(0);

                instances.instancesForce()[j] += force;
            }

            instances.instancesForce()[i] = self_force;
        }
    }
}