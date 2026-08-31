#pragma once

#include <vector>

#include "glw/core/vao.hpp"
#include "glw/structure/vector.hpp"


namespace engine::scene {
    struct Instances;
}

namespace engine::gfx {
    struct InstancesBuffer {
        glw::VAO& vertexFormat;

        glw::vector<glm::vec4> instancesHeaders;

        int bindingPoint;

        InstancesBuffer(glw::VAO& vertex_format, int binding_point) : vertexFormat(vertex_format), bindingPoint(binding_point) {}

        int push(std::vector<glm::vec4>& instances);

        int index(scene::Instances& instances);
    };
}