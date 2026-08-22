#include "engine/gfx/buffer/instances_buffer.hpp"

#include "util.hpp"
#include "engine/scene/instances.hpp"


namespace engine::gfx {
    void InstancesBuffer::push(std::vector<glm::vec4>& instancesComponent) {
        instancesHandles.push_back(instancesComponent, [this] {
            vertexFormat.attachBuffer(
                instancesHandles.getBuffer(),
                bindingPoint, 0,
                util::bytesof<glm::vec4>());
        });
    }

    void InstancesBuffer::index(scene::Instances& instances) {
        push(instances.positions);

        instances.id = nextFreeIndex;
        nextFreeIndex++;
    }
}
