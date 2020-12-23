#pragma once

#include <string.h>
#include <Arduino.h>

#include <map>

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
        std::map<String, String> tags;
        std::map<String, String> fields;
        unsigned long long timestamp;
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

        bool have_measurement = false;
        bool have_tags = false;
        bool have_fields = false;
        bool have_timestamp = false;

        for(String::size_type i = 0; i < data.length(); i++) {
            if(!have_measurement) {
                if(data[i] != ' ') {
                    lp.measurement.append(data[i]);
                    continue;
                } else {
                    have_measurement = true;
                    continue;
                }
            }

            if(!have_tags) {
                if(data[i] != ' ') {
                    lp.measurement.append(data[i]);
                    continue;
                } else {
                    have_measurement = true;
                    continue;
                }
            }

            if(!have_fields) {
                if(data[i] != ' ') {
                    lp.measurement.append(data[i]);
                    continue;
                } else {
                    have_measurement = true;
                    continue;
                }
            }

            if(!have_timestamp) {
                if(data[i] != ' ') {
                    lp.measurement.append(data[i]);
                    continue;
                } else {
                    have_measurement = true;
                    continue;
                }

            }

        }

        return lp;
    }
}