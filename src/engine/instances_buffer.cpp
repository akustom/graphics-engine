#include "engine/instances_buffer.hpp"

#include "util.hpp"
#include "engine/instances.hpp"


namespace engine {
    InstancesBuffer::IndexData InstancesBuffer::getInstancesOffset(Instances& instances) {
        return indexedInstances[instances.id];
    }

    void InstancesBuffer::push(std::vector<glm::vec4>& instancesComponent) {
        if (!batchHeader.size) {
            if (batchHeader.size + instancesComponent.size() > batchHeader.capacity) {
                batchHeader.capacity = 2 * std::max(batchHeader.size, static_cast<int>(instancesComponent.size()));

                glw::VBO tempVBO;
                tempVBO.allocateBuffer<glm::vec4>(batchHeader.capacity, GL_DYNAMIC_STORAGE_BIT);
                tempVBO.copyData<glm::vec4>(instancesBuffer, batchHeader.size);

                instancesBuffer = std::move(tempVBO);
                vertexFormat.attachBuffer(instancesBuffer, bindingPoint, 0, util::bytesof<glm::vec4>());
            }
            instancesBuffer.pushData(static_cast<int>(util::bytesof<glm::vec4>()) * batchHeader.size, instancesComponent);

        } else {
            instancesBuffer.allocateBuffer(instancesComponent);
            vertexFormat.attachBuffer(
                instancesBuffer,
                bindingPoint, 0,
                util::bytesof<glm::vec4>()
                );
        }
    }

    void InstancesBuffer::index(Instances& instances) {
        push(instances.positions);

        instances.id = static_cast<int>(indexedInstances.size());
        indexedInstances.emplace_back(
            instances.instanceCount,
            batchHeader.size);

        batchHeader.size += instances.instanceCount;
    }
}
