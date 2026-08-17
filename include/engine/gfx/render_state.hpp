#pragma once


namespace engine::win {
    struct Window;
}

namespace engine::gfx {
    void setViewport(win::Window& window);

    void enableDepthTest(bool enable = true);
}