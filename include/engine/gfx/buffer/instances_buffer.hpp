#pragma once

#include <vector>
#include <boost/unordered/unordered_flat_map.hpp>

#include "glw/core/vao.hpp"
#include "glw/structure/vector.hpp"

#include "engine/core/handle_issuer.hpp"


namespace engine::scene {
    struct Instances;
}

namespace engine::gfx {
    struct InstancesBuffer {
        glw::VAO& vertexFormat;

        glw::vector<glm::vec4> instancesHeaders;

        core::HandleIssuer issuer;

        boost::unordered_flat_map<core::Handle, glw::HeaderPair<1>> registry;

        int bindingPoint;

        InstancesBuffer(glw::VAO& vertex_format, int binding_point) : vertexFormat(vertex_format), bindingPoint(binding_point) {}

        const glw::HeaderPair<1>& operator[](const core::Handle& handle) const;

        void push(std::vector<glm::vec4>& instances);

        const core::Handle& index(scene::Instances& instances);
    };
}