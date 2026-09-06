#pragma once

namespace DEBUG {
    enum class LEVEL {
        INFO = 0,

        MINOR = 1,
        WARN = 2,
        SEVERE = 3,
    };

    inline const char* s_LEVEL(LEVEL level) {
        if (level == LEVEL::INFO) return "INFO";
        if (level == LEVEL::MINOR) return "MINOR";
        if (level == LEVEL::WARN)  return "WARN";
        if (level == LEVEL::SEVERE) return "SEVERE";
        return "UNKNOWN";
    }
};