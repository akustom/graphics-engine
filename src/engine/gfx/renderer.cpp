#include "engine/gfx/renderer.hpp"

#include "engine/geometry/mesh.hpp"
#include "engine/scene/instances.hpp"
#include "glw/render.hpp"

#include "engine/gfx/buffer/mesh_buffer.hpp"
#include "engine/gfx/buffer/instances_buffer.hpp"

#include "tracy/Tracy.hpp"


namespace engine::gfx {
    void Renderer::render(geo::Mesh& mesh, scene::Instances& instances) const {
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
