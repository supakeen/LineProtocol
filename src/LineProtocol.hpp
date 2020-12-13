#pragma once

#include <string.h>

#include <Arduino.h>

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

namespace LineProtocol {
    struct line_protocol {
        String measurement;
        String room;
        String value;
    };

    String line_protocol_format(struct line_protocol *lp) {
        String formatted = "";
        formatted += lp->measurement;
        formatted += ",room=";
        formatted += lp->room;
        formatted += " ";
        formatted += " value=";
        formatted += lp->value;
        return formatted;
    }

    struct line_protocol line_protocol_parse(String &data) {
        struct line_protocol lp;

        String metas = getValue(data, ' ', 0);
        String field = getValue(data, ' ', 1);

        lp.measurement = getValue(metas, ',', 0);
        lp.room = getValue(getValue(metas, ',', 1), '=', 1);
        lp.value = getValue(field, '=', 1);

        return lp;
    }
}