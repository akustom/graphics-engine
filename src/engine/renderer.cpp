#include "engine/renderer.hpp"

#include "gfx/mesh.hpp"
#include "engine/instances.hpp"
#include "glw/render.hpp"

#include "engine/mesh_buffer.hpp"
#include "engine/instances_buffer.hpp"

#include "tracy/Tracy.hpp"


namespace engine {
    void Renderer::render(gfx::Mesh& mesh, Instances& instances) const {
        ZoneScoped;
        MeshBuffer::IndexData meshOffset = meshBuffer.getMeshOffset(mesh);
        InstancesBuffer::IndexData instancesOffset = instancesBuffer.getInstancesOffset(instances);

        glw::drawInstancesBaseVertexBaseInstances(
            instancesOffset.instances_count,
            meshOffset.indexCount,
            meshOffset.ebo_offset,
            meshOffset.vbo_offset,
            instancesOffset.buffer_offset);
    }
}
