#include "engine/gfx/render_state.hpp"

#include "engine/window/window.hpp"
#include "glad/glad.h"


namespace engine::gfx {
    void setViewport(win::Window& window) {
        int width, height;
        window.getWindowSize(&width, &height);

        glViewport(0, 0, width, height);
    }

    void enableDepthTest(bool enable)  {
        if (enable) {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }
}
