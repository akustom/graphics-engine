#pragma once

#include <vector>
#include <iostream>

#include <glm/glm.hpp>


namespace engine::scene {
    class Instances {
        struct Parameters {
            glm::vec3 pos = glm::vec3(0);
            glm::vec3 vel = glm::vec3(0);
            glm::vec3 accel = glm::vec3(0);
            glm::vec3 force = glm::vec3(0);

            float mass = 1.0f;
        };

    public:
        struct Instance {
            glm::vec4& position;
            glm::vec4& velocity;
            glm::vec4& acceleration;
            glm::vec4& force;

            float& mass;

            Instance(glm::vec4& pos, glm::vec4& vel, glm::vec4& accel, glm::vec4& force, float& mass) : position(pos), velocity(vel), acceleration(accel), force(force), mass(mass) {}
        };

        struct Iterator {
            Instances& container;
            std::size_t index;

            Instance operator*() const {
                return container[index];
            }

            Iterator& operator++() {
                ++index;
                return *this;
            }

            bool operator!=(const Iterator& other) const {
                return index != other.index;
            }
        };

        Iterator begin() { return Iterator{*this, 0}; }
        Iterator end()   { return Iterator{*this, instanceCount}; }

        Instance operator[](std::size_t index); // getting an instance

        void createInstance(Parameters test);
        void clear();

        std::vector<glm::vec4>& instancesPos();
        std::vector<glm::vec4>& instancesVel();
        std::vector<glm::vec4>& instancesAccel();
        std::vector<glm::vec4>& instancesForce();
        std::vector<float>& instancesMasses();

        [[nodiscard]] std::size_t size() const;

    private:
        std::vector<glm::vec4> positions;
        std::vector<glm::vec4> velocities;
        std::vector<glm::vec4> accelerations;
        std::vector<glm::vec4> forces;
        std::vector<float> masses;

        std::size_t instanceCount = 0;
    };
}