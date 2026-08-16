#include "engine/gfx/buffer/render_batch.hpp"

#include "engine/geometry/mesh.hpp"
#include "engine/scene/instances.hpp"


namespace engine::gfx {
    void RenderBatch::index(geo::Mesh& mesh) {
        meshBuffer.index(mesh);
    }
    void RenderBatch::index(scene::Instances& instances) {
        instancesBuffer.index(instances);
    }
}
