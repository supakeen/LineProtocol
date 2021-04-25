/* This is a small header-only Arduino/C++ library to format or parse data in
 * the [InfluxDB Line
 * Protocol](https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/).
 *
 * The InfluxDB Line Protocol looks like this:
 * ```
 * <measurement>[,<tag_key>=<tag_value>[,<tag_key>=<tag_value>]]
 * <field_key>=<field_value>[,<field_key>=<field_value>] [<timestamp>]
 * ``` */

#pragma once

#include <stdlib.h>

#include <Arduino.h>

#include <list>
#include <map>

using namespace std;

namespace LineProtocol {
enum parse_state {
  PARSE_START = 0,
  PARSE_MEASUREMENT = 1,
  PARSE_TAGS = 2,
  PARSE_FIELDS = 3,
  PARSE_TIMESTAMP = 4,
  PARSE_END = 5,
  PARSE_ERR = 6,
};

enum subparse_state {
  SUBPARSE_START = 0,
  SUBPARSE_KEY = 1,
  SUBPARSE_VAL = 2,
  SUBPARSE_END = 3,
};

class Message {
public:
  String measurement;
  std::map<String, String> tags;
  std::map<String, String> fields;
  unsigned long long timestamp;

  Message(String measurement, std::map<String, String> fields,
          std::map<String, String> tags, unsigned long long timestamp)
      : measurement(measurement), fields(fields), tags(tags),
        timestamp(timestamp){};

  Message(String data) {
    enum parse_state state = PARSE_START;
    enum subparse_state substate = SUBPARSE_START;

    bool in_escape = false;

    bool have_comma = false;
    bool have_space = false;

    bool at_end = false;

    String key;
    String val;

    for (size_t i = 0; i < data.length(); i++) {
      if (i + 1 == data.length()) {
        at_end = true;
      }

      /* The following characters all have special meaning if they're not
       * being escaped. Most of them are either value separators or
       * section separators. */

      if (!in_escape) {
        if (data[i] == '\\') {
          in_escape = true;
          continue;
        }

        have_comma = data[i] == ',';
        have_space = data[i] == ' ';
      }

      if (state == PARSE_START)
        state = PARSE_MEASUREMENT;

      /* The measurement is the initial data it needs to be non-zero
       * length before we can progress into the next step. */

      if (state == PARSE_MEASUREMENT) {

        /* If we encounter the , separator we move into tag parsing. */
        if (have_comma) {

          /* There needs to be at least one character of measurement
           * before we can accept tags. */

          if (!measurement.length()) {
            state = PARSE_ERR;
            continue;
          }

          state = PARSE_TAGS;
          continue;
        }

        /* If we encounter the ' ' separator we skip over tags into
         * fields. */
        if (have_space) {

          /* There needs to be at least one character of measurement
           * before we can accept fields . */

          if (!measurement.length()) {
            state = PARSE_ERR;
            continue;
          }

          state = PARSE_FIELDS;
          continue;
        }

        /* Add the character to the measurement name. */

        measurement += data[i];
        continue;

      } else if (state == PARSE_TAGS) {
        if (substate == SUBPARSE_START)
          substate = SUBPARSE_KEY;

        if (substate == SUBPARSE_KEY) {
          if (have_comma || have_space || at_end) {
            throw "Error";
          }

          if (data[i] == '=') {
            substate = SUBPARSE_VAL;
            continue;
          }

          key += data[i];
          continue;
        } else if (substate == SUBPARSE_VAL) {
          if (have_comma || have_space || at_end) {
            if (at_end)
              val += data[i];

            tags[key] = val;

            key.remove(0);
            val.remove(0);

            if (have_space)
              state = PARSE_FIELDS;
            if (at_end)
              state = PARSE_END;

            substate = SUBPARSE_KEY;

            continue;
          }

          val += data[i];
          continue;
        }
      } else if (state == PARSE_FIELDS) {
        if (substate == SUBPARSE_KEY) {
          if (have_comma || have_space || at_end) {
            throw "Error";
          }

          if (data[i] == '=') {
            substate = SUBPARSE_VAL;
            continue;
          }

          key += data[i];
          continue;
        } else if (substate == SUBPARSE_VAL) {
          if (have_comma || have_space || at_end) {
            if (at_end)
              val += data[i];

            fields[key] = val;

            key.remove(0);
            val.remove(0);

            if (have_space)
              state = PARSE_TIMESTAMP;
            if (at_end)
              state = PARSE_END;

            substate = SUBPARSE_KEY;

            continue;
          }

          val += data[i];
          continue;
        }
      } else if (state == PARSE_TIMESTAMP) {
      } else if (state == PARSE_ERR) {
        throw "Error";
      } else {
        throw "Error";
      }
    }
  };

  int validate(std::list<String> tags_argument,
               std::list<String> fields_argument) {
    for (auto tag : tags_argument) {
      if (!tags.count(tag))
        return 1;
    }

    for (auto field : fields_argument) {
      if (!fields.count(field))
        return 1;
    }

    return 0;
  }
};
} // namespace LineProtocol
