#pragma once


namespace win {
    struct CursorContext {
        float lastX = 0;
        float lastY = 0;

        float offsetX = 0;
        float offsetY = 0;

        bool initialized = false;

        void clearOffsets() {
            offsetX = 0;
            offsetY = 0;
        }
    };
}