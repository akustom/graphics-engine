#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "gfx/mesh.hpp"


namespace engine {
    struct Instances {
        int instanceCount = 0;

        std::vector<glm::vec4> positions;
        std::vector<glm::vec4> velocities;
        std::vector<glm::vec4> accelerations;

        gfx::Mesh* mesh;

        Instances(gfx::Mesh& instance_mesh) : mesh(&instance_mesh) {}

        void bindToMesh(gfx::Mesh& l_mesh);

        void createInstance(
            const glm::vec3& position = {0, 0, 0},
            const glm::vec3& velocity = {0, 0, 0},
            const glm::vec3& acceleration = {0, 0, 0}
            );
    };
}