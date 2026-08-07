#pragma once

#include <vector>

#include "glw/buffer.hpp"
#include "glw/vao.hpp"


namespace engine {
    struct Instances;

    struct InstancesBuffer { // wip
        struct IndexData {
            int instances_count = 0;
            int buffer_offset = 0;

            IndexData(unsigned int size, unsigned int offset) : instances_count(size), buffer_offset(offset) {}
        };

        struct BatchHeader {
            unsigned int size = 0;
            unsigned int capacity = 0;
        };

        std::vector<IndexData> indexedInstances;

        glw::VAO& vertexFormat;
        glw::Buffer instancesBuffer;

        BatchHeader batchData;

        int bindingLocation;

        InstancesBuffer(glw::VAO& vertex_format, int binding_loc) : vertexFormat(vertex_format), bindingLocation(binding_loc) {
            vertexFormat.formatAttribute(3, binding_loc, 4, GL_FLOAT, 0);
            vertexFormat.setAttributeDivisor(binding_loc, 1);
        }

        IndexData getInstancesOffset(Instances& instances);

        void push(Instances& instances);

        void indexInstances(Instances& instances);
    };
}