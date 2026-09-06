#pragma once

#include <iostream>
#include <vector>

#include "enums.hpp"
#include "util.hpp"


namespace DEBUG { // WIP
    struct LOG {
        const char* message;
        LEVEL severity;

        LOG(std::string_view debug_msg, LEVEL severity) :
            message(debug_msg.data()), severity(severity) {}
    };

    inline std::vector<LOG> logged_items;

    inline const LOG& log(const LOG item) {
        logged_items.push_back(item);

        return logged_items.back();
    }

    inline void print() {
        for (const LOG& item : logged_items) {
            util::print("MSG: ", item.message, " | SEVERITY: ", s_LEVEL(item.severity));
        }
    }
}