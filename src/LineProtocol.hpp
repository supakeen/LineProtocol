#pragma once

#include <Arduino.h>

namespace LineProtocol {
    struct line_protocol {
    };

    int line_protocol_format(struct line_protocol *line_protocol, String &data) {
        return 0;
    }

    int line_protocol_parse(struct line_protocol *line_protocol, String &data) {
        return 0;
    }
}