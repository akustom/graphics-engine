#include "engine/gfx/buffer/instances_buffer.hpp"

#include "util.hpp"
#include "engine/scene/instances.hpp"


namespace engine::gfx {
    int InstancesBuffer::push(std::vector<glm::vec4>& instancesComponent) {
        return instancesHeaders.push_back(instancesComponent, vertexFormat,
            instancesHeaders.getBuffer(),
            bindingPoint, 0,
            util::bytesof<glm::vec4>()
        );
    }

    int InstancesBuffer::index(scene::Instances& instances) {
        return push(instances.positions);
    }
}
