#pragma once

#include "engine/gfx/buffer/render_batch.hpp"

namespace engine::geo {
    struct Mesh;
}

namespace engine::scene {
    struct Instances;
}

namespace engine::gfx {
    struct Renderer {
        RenderBatch& renderBatch;

        Renderer(RenderBatch& render_batch) : renderBatch(render_batch) {}

        void render(geo::Mesh& mesh, scene::Instances& instances) const;
    };
}
