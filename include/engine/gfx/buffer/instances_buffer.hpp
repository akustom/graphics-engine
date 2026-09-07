#pragma once

#include <vector>

#include "glw/core/vao.hpp"
#include "glw/structure/vector.hpp"

#include "engine/core/registry.hpp"


namespace engine::scene {
    struct Instances;
}

namespace engine::gfx {
    class InstancesBuffer {
    public:
        InstancesBuffer(glw::VAO& vertex_format, unsigned int binding_point) : vertexFormat(vertex_format), bindingPoint(binding_point) {}

        const glw::HeaderPair<1>& operator[](core::rHandle handle) const;
        void push(std::vector<glm::vec4>& instances);
        core::rHandle index(scene::Instances& instances);
    private:
        glw::VAO& vertexFormat;
        glw::vector<glm::vec4> instancesHeaders;
        core::registry<glw::HeaderPair<1>> registry;

        unsigned int bindingPoint;
    };
}