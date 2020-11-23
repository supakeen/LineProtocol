#pragma once

#include <Arduino.h>

namespace LineProtocol {
    struct line_protocol {
    };

    String line_protocol_format(struct line_protocol *line_protocol) {
        String formatted = "1234";
        return formatted;
    }

    struct line_protocol line_protocol_parse(String &data) {
        return 0;
    }
}