#pragma once

#include <vector>
#include <boost/unordered/unordered_flat_map.hpp>

#include "glw/core/vao.hpp"
#include "glw/structure/vector.hpp"

#include "engine/core/registry.hpp"


namespace engine::scene {
    struct Instances;
}

namespace engine::gfx {
    struct InstancesBuffer {
        glw::VAO& vertexFormat;

        glw::vector<glm::vec4> instancesHeaders;

        core::registry<glw::HeaderPair<1>> registry;

        int bindingPoint;

        InstancesBuffer(glw::VAO& vertex_format, int binding_point) : vertexFormat(vertex_format), bindingPoint(binding_point) {}

        const glw::HeaderPair<1>& operator[](core::rHandle handle) const;

        void push(std::vector<glm::vec4>& instances);

        core::rHandle index(scene::Instances& instances);
    };
}