# LineProtocol

This is a small header-only Arduino/C++ library to format or parse data in the [InfluxDB Line Protocol](https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/).

## Format

The InfluxDB Line Protocol looks like this:

```
<measurement>[,<tag_key>=<tag_value>[,<tag_key>=<tag_value>]] <field_key>=<field_value>[,<field_key>=<field_value>] [<timestamp>]
```

## Usage

### Parsing

You can parse some data into a `struct line_protocol` like so:

```c++
#include <LineProtocol.h>

struct line_protocol lp;

if(line_protocol_parse(&lp, "measurement,key=value key=value")) {
  // Error :(
}

// Use `lp` here.
```

### Formatting

To be documented.
