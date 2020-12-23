#pragma once

#include <stdlib.h>
#include <string.h>

#include <map>
#include <string>

using namespace std;

namespace LineProtocol {
    struct line_protocol {
        char measurement[64];
        map<string, string> tags;
        map<string, string> fields;
        unsigned long long timestamp;
    };

    string line_protocol_format(struct line_protocol *lp) {
        string formatted = "";
        formatted += lp->measurement;
        formatted += ",room=";
        formatted += lp->tags["room"];
        formatted += " ";
        formatted += " value=";
        formatted += lp->fields["value"];
        return formatted;
    }

    int line_protocol_parse(struct line_protocol &lp, char const *data) {
        bool have_measurement = false;
        size_t index_measurement = 0;

        bool have_tags = false;
        bool have_fields = false;
        bool have_timestamp = false;

        for(size_t i = 0; i < strlen(data); i++) {
            if(!have_measurement) {
                if(data[i] != ' ' && data[i] != ',') {
                    lp.measurement[index_measurement] = data[i];
                    index_measurement++;
                    continue;
                } else {
                    have_measurement = true;
                    continue;
                }
            }

            if(!have_tags) {
            }

            if(!have_fields) {
            }

            if(!have_timestamp) {
            }

        }

        return 0;
    }
}
