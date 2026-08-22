#pragma once

#include <vector>

#include "glw/primitive/vao.hpp"
#include "glw/structure/vector.hpp"


namespace engine::scene {
    struct Instances;
}

namespace engine::gfx {
    struct InstancesBuffer {
        glw::VAO& vertexFormat;

        glw::vector<glm::vec4> instancesHandles;

        int bindingPoint;
        int nextFreeIndex = 0;

        InstancesBuffer(glw::VAO& vertex_format, int binding_point) : vertexFormat(vertex_format), bindingPoint(binding_point) {}

        void push(std::vector<glm::vec4>& instances);

        void index(scene::Instances& instances);
    };
}