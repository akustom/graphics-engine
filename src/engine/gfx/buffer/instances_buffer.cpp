#include "engine/gfx/buffer/instances_buffer.hpp"

#include "util.hpp"
#include "engine/core/handle_issuer.hpp"
#include "engine/scene/instances.hpp"


namespace engine::gfx {
    const glw::HeaderPair<1>& InstancesBuffer::operator[](const core::Handle& handle) const {
        return registry.at(handle);
    }

    void InstancesBuffer::push(std::vector<glm::vec4>& instancesComponent) {
        instancesHeaders.push_back(instancesComponent, vertexFormat,
            instancesHeaders.getBuffer(),
            bindingPoint, 0,
            util::bytesof<glm::vec4>()
        );
    }

    const core::Handle& InstancesBuffer::index(scene::Instances& instances) {
        push(instances.positions);

        auto [it, inserted] = registry.emplace(
            issuer.getUnique(),
            glw::HeaderPair{instancesHeaders.back()}
        );

        return it->first;
    }
}
