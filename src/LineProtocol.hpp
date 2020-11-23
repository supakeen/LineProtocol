#pragma once

#include <Arduino.h>

namespace LineProtocol {
    struct line_protocol {
        String measurement;
    };

    String line_protocol_format(struct line_protocol *lp) {
        String formatted = "";
        formatted += lp->measurement;
        return formatted;
    }

    struct line_protocol line_protocol_parse(String &data) {
        struct line_protocol lp;
        return lp;
    }
}