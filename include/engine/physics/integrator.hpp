#pragma once

#include <vector>
#include <algorithm>
#include <glm/vec4.hpp>
#include <tracy/Tracy.hpp>

#include "engine/core/simd/s_vec4.hpp"
#include "engine/scene/instances.hpp"


namespace engine::phy {
    struct VelocityVerlet {
    public:
        template <void(*...forces)(scene::Instances& instances)>
        static void step(scene::Instances& instances, float dt) {
            ZoneScoped;

            step_first(instances, dt);

            clear_forces(instances);
            apply_forces<forces...>(instances);

            step_second(instances, dt);
        }

    private:
        static void step_first(scene::Instances& instances, float dt) {
            const std::size_t items = instances.size();
            const std::size_t tail  = items - items % simd::OFFSET_256::vec4;

            simd::__m256 m256_dt   = simd::_mm256_set1_vec4(dt);
            simd::__m256 m256_half = simd::_mm256_set1_vec4(0.5f);

            for (std::size_t i = 0; i < tail; i += simd::OFFSET_256::vec4) {
                simd::__m256 m256_accel_sdt = simd::_mm256_loadu_vec4(&instances.instancesAccel()[i]);

                m256_accel_sdt = simd::_mm256_mul_vec4(m256_accel_sdt, m256_half);
                m256_accel_sdt = simd::_mm256_mul_vec4(m256_accel_sdt, m256_dt);

                simd::__m256 m256_accel_ddt = simd::_mm256_mul_vec4(m256_accel_sdt, m256_dt);

                simd::__m256 m256_vel = simd::_mm256_loadu_vec4(&instances.instancesVel()[i]);
                simd::__m256 m256_vel_p = simd::_mm256_fmadd_vec4(m256_vel, m256_dt, m256_accel_ddt);

                simd::__m256 m256_pos = simd::_mm256_loadu_vec4(&instances.instancesPos()[i]);
                m256_pos = simd::_mm256_add_vec4(m256_pos, m256_vel_p);
                simd::_mm256_storeu_vec4(&instances.instancesPos()[i], m256_pos);   // update pos -> x(t + dt)

                m256_vel = simd::_mm256_add_vec4(m256_vel, m256_accel_sdt);
                simd::_mm256_storeu_vec4(&instances.instancesVel()[i], m256_vel);   // update vel -> v(t + dt/2)
            }

            for (std::size_t i = tail; i < items; i++) {
                instances.instancesPos()[i] += instances.instancesVel()[i] * dt + 1.0f/2.0f * instances.instancesAccel()[i] * dt * dt;
                instances.instancesVel()[i] += 1.0f/2.0f * instances.instancesAccel()[i] * dt;
            }
        }

        static void clear_forces(scene::Instances& instances) {
            std::ranges::fill(instances.instancesForce(), glm::vec4(0));
        }

        template <void(*...forces)(scene::Instances& instances)>
        static void apply_forces(scene::Instances& instances) {
            (forces(instances), ...);
        }

        static void step_second(scene::Instances& instances, float dt) {
            const std::size_t items = instances.size();
            const std::size_t tail  = items - items % simd::OFFSET_256::vec4;

            simd::__m256 m256_dt   = simd::_mm256_set1_vec4(dt);
            simd::__m256 m256_half = simd::_mm256_set1_vec4(0.5f);

            for (std::size_t i = 0; i < tail; i += simd::OFFSET_256::vec4) {
                simd::__m256 m256_force = simd::_mm256_loadu_vec4(&instances.instancesForce()[i]);
                simd::__m256 m256_mass  = simd::_mm256_alignf_vec4(
                    instances.instancesMasses()[i],
                    instances.instancesMasses()[i+1]);

                simd::__m256 m256_accel = simd::_mm256_div_vec4(m256_force, m256_mass);
                simd::_mm256_storeu_vec4(&instances.instancesAccel()[i], m256_accel);    // update accel -> a(t + dt)

                simd::__m256 m256_accel_v = simd::_mm256_mul_vec4(m256_half, m256_accel);
                m256_accel_v = simd::_mm256_mul_vec4(m256_accel_v, m256_dt);

                simd::__m256 m256_vel = simd::_mm256_loadu_vec4(&instances.instancesVel()[i]);
                m256_vel = simd::_mm256_add_vec4(m256_vel, m256_accel_v);
                simd::_mm256_storeu_vec4(&instances.instancesVel()[i], m256_vel);    // update vel -> v(t + dt)
            }

            for (std::size_t i = tail; i < items; i++) {
                instances.instancesAccel()[i] = instances.instancesForce()[i]/instances.instancesMasses()[i];
                instances.instancesVel()[i]  += 1.0f/2.0f * instances.instancesAccel()[i] * dt;
            }
        }
    };

    using VelVer = VelocityVerlet;
    using V_V = VelocityVerlet;
}
