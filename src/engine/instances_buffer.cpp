#include "engine/instances_buffer.hpp"

#include "util.hpp"
#include "engine/instances.hpp"


namespace engine {
    InstancesBuffer::IndexData InstancesBuffer::getInstancesOffset(Instances& instances) {
        return indexedInstances[instances.id];
    }

    void InstancesBuffer::push(Instances& instances) {
        instancesBuffer.allocateBuffer(instances.positions, GL_DYNAMIC_STORAGE_BIT);
        vertexFormat.attachBuffer(instancesBuffer, bindingLocation, 0, util::bytesof<glm::vec4>());
    }

    void InstancesBuffer::index(Instances& instances) {
        push(instances);

        instances.id = static_cast<int>(indexedInstances.size());
        indexedInstances.emplace_back(
            instances.instanceCount,
            batchHeader.size);

        batchHeader.size += instances.instanceCount;
    }
}
