# LineProtocol

This is a small header-only Arduino/C++ library to format or parse data in the [InfluxDB Line Protocol](https://docs.influxdata.com/influxdb/v2.0/reference/syntax/line-protocol/).
The build system used is platformio.

## Format

The InfluxDB Line Protocol looks like this:

```
<measurement>[,<tag_key>=<tag_value>[,<tag_key>=<tag_value>]] <field_key>=<field_value>[,<field_key>=<field_value>] [<timestamp>]
```

Which offers a lot of flexibility for your boards and other applications. The
reason for this library to exist is that speaking a common format over MQTT
allows you to add display boards without writing custom code to understand the
formats you have for each board and to circumvent the step of writing custom code
to reformat boards into the way you like it.

## Usage

### Parsing

You can parse some data into a `struct line_protocol` like so:

```cpp
#include <LineProtocol.h>

struct line_protocol lp;

if(line_protocol_parse(&lp, "measurement,key=value key=value")) {
  // Error :(
}

// Use `lp` here.
```

### Formatting

Unsupported in `0.1.0` but the next feature on the list.

### The struct

`LineProtocol` uses the `struct line_protocol`, its layout is as follows:

```cpp
struct line_protocol {
    String measurement;
    map<String, String> tags;
    map<String, String> fields;
    unsigned long long timestamp;
};

```

## Testing

To test the library make sure you connect an `esp32` board then run:

```
pio test -e esp32
```

Which will upload firmware and run tests while fetching the results remotely.
I'm working on providing native tests for CI as well, but for that I have to
struggle some more with `String` types.
