#include "engine/gfx/buffer/instances_buffer.hpp"

#include "util.hpp"
#include "engine/scene/instances.hpp"


namespace engine::gfx {
    const glw::HeaderPair<1>& InstancesBuffer::operator[](core::rHandle handle) const {
        return registry.at(handle);
    }

    void InstancesBuffer::push(std::vector<glm::vec4>& instancesComponent) {
        instancesHeaders.push_back(instancesComponent, vertexFormat,
            instancesHeaders.getBuffer(),
            bindingPoint, 0,
            util::bytesof<glm::vec4>()
        );
    }

    core::rHandle InstancesBuffer::index(scene::Instances& instances) {
        push(instances.positions);

        auto issued = registry.create(glw::HeaderPair{instancesHeaders.back()});

        return issued;
    }
}
