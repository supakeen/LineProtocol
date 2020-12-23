#pragma once

#include <stdlib.h>
#include <string.h>

#include <map>
#include <string>

using namespace std;

namespace LineProtocol {
    struct line_protocol {
        string measurement;
        map<string, string> tags;
        map<string, string> fields;
        unsigned long long timestamp;
    };

    enum parse_state {
        PARSE_START = 0,
        PARSE_MEASUREMENT = 1,
        PARSE_TAGS = 2,
        PARSE_FIELDS = 3,
        PARSE_TIMESTAMP = 4,
        PARSE_END = 5,
    };

    enum subparse_state {
        SUBPARSE_START = 0,
        SUBPARSE_KEY = 1,
        SUBPARSE_VAL = 2,
        SUBPARSE_END = 3,
    };

    void line_protocol_format(struct line_protocol *lp) {
    }

    int line_protocol_parse(struct line_protocol &lp, char const *data) {
        bool have_tags = false;
        bool have_fields = false;
        bool have_timestamp = false;

        enum parse_state state = PARSE_START;
        enum subparse_state substate = SUBPARSE_START;

        bool in_escape = false;
        bool in_quotes = false;

        bool have_sep0 = false;
        bool have_sep1 = false;

        string key;
        string val;

        for(size_t i = 0; i < strlen(data); i++) {
            if(!in_escape) {
               if(data[i] == '\\') {
                   in_escape = true;
                   continue;
               }

               if(data[i] == ',') {
                   have_sep0 = true;
               } else {
                   have_sep0 = false;
               }

               if(data[i] == ' ') {
                   have_sep1 = true;
               } else {
                   have_sep1 = false;
               }
            }

            if(state == PARSE_START) {
                state = PARSE_MEASUREMENT;
            }

            if(state == PARSE_MEASUREMENT) {
                if(have_sep0) {
                    state = PARSE_TAGS;
                    continue;
                }

                if(have_sep1) {
                    state = PARSE_FIELDS;
                    continue;
                }

                lp.measurement.push_back(data[i]);
                continue;
            }

            if(state == PARSE_TAGS) {
                if(substate == SUBPARSE_START) {
                    substate = SUBPARSE_KEY;
                }

                if(substate == SUBPARSE_KEY) {
                    if(have_sep0 || have_sep1) {
                        return -1;
                    }

                    if(data[i] == '=') {
                        substate = SUBPARSE_VAL;
                        continue;
                    }

                    key.push_back(data[i]);
                    continue;
                }

                if(substate == SUBPARSE_VAL) {
                    if(have_sep0 || have_sep1) {
                        lp.tags[key] = val;

                        key.clear();
                        val.clear();

                        substate = SUBPARSE_KEY;

                        if(have_sep1) {
                            state = PARSE_FIELDS;
                        }

                        continue;
                    }

                    val.push_back(data[i]);
                    continue;
                }
            }

            if(state == PARSE_FIELDS) {
                if(substate == SUBPARSE_KEY) {
                }

                if(substate == SUBPARSE_VAL) {
                }
            }

            if(state == PARSE_TIMESTAMP) {
            }

            state = PARSE_END;
        }

        if(state != PARSE_END) {
            return -1;
        }

        return 0;
    }
}
