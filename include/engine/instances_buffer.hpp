#pragma once

#include <vector>

#include "glw/buffer.hpp"
#include "glw/vao.hpp"


namespace engine {
    struct Instances;

    struct InstancesBuffer { // todo wip, make the push instances more flexible, supporting more instances, etc
        struct IndexData {
            int instances_count = 0;
            int buffer_offset = 0;

            IndexData(unsigned int size, unsigned int offset) : instances_count(size), buffer_offset(offset) {}
        };

        struct BatchHeader {
            int size = 0;
            int capacity = 0;
        };

        std::vector<IndexData> indexedInstances;

        glw::VAO& vertexFormat;
        glw::Buffer instancesBuffer;

        BatchHeader batchHeader;

        int bindingPoint;

        InstancesBuffer(glw::VAO& vertex_format, int binding_point) : vertexFormat(vertex_format), bindingPoint(binding_point) {
            vertexFormat.formatAttribute(3, binding_point, 4, GL_FLOAT, 0);
            vertexFormat.setAttributeDivisor(binding_point, 1);
        }

        IndexData getInstancesOffset(Instances& instances);

        void push(std::vector<glm::vec4>& instances);

        void index(Instances& instances);
    };
}