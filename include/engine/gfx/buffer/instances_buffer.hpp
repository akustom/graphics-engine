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
        glw::HeaderPair<1> operator[](core::Handle handle) const;

        core::Handle index(scene::Instances& instances);
        void modify(core::Handle instances, scene::Instances& instancesData);

    private:
        struct HeaderIndex {
            uint32_t instances_i;
        };

        glw::VAO& vertexFormat;
        glw::vector<glm::vec4> instancesHeaders;
        core::registry<HeaderIndex> registry;

        unsigned int bindingPoint;

        void push(std::vector<glm::vec4>& instances);
    };
}