#include "engine/gfx/buffer/instances_buffer.hpp"

#include "util.hpp"
#include "engine/scene/instances.hpp"


namespace engine::gfx {
    glw::HeaderPair<1> InstancesBuffer::operator[](core::Handle handle) const {
        return {instancesHeaders[registry.at(handle)]};
    }

    core::Handle InstancesBuffer::index(scene::Instances& instances) {
        push(instances.instancesPos());

        auto issued = registry.push(static_cast<uint32_t>(instancesHeaders.size()) - 1);

        return issued;
    }

    void InstancesBuffer::modify(core::Handle handle, scene::Instances& instancesData) {
        instancesHeaders.modify(
            instancesHeaders[registry.at(handle)], instancesData.instancesPos(),
            vertexFormat,
                instancesHeaders.getBuffer(),
                bindingPoint, 0,
                sizeof(glm::vec4));
    }

    void InstancesBuffer::push(std::vector<glm::vec4>& instancesComponent) {
        instancesHeaders.push_back(instancesComponent, vertexFormat,
            instancesHeaders.getBuffer(),
            bindingPoint, 0,
            sizeof(glm::vec4));
    }
}
