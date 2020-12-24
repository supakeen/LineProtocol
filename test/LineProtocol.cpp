#include "../src/LineProtocol.h"
#include "catch/catch.hpp"

#include <stdio.h>
#include <stdlib.h>


TEST_CASE("line_protocol_parse_0") {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, "measurement foo=bar");

    CHECK(result == 0);
    CHECK("measurement" == lp.measurement);
}

TEST_CASE("line_protocol_parse_1") {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, "test foo=bar");

    CHECK(result == 0);
    CHECK("test" == lp.measurement);
}

TEST_CASE("line_protocol_parse_2") {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, "test,bar=foo foo=bar");

    CHECK(result == 0);
    CHECK("test" == lp.measurement);
    CHECK("foo" == lp.tags["bar"]);
    CHECK("bar" == lp.fields["foo"]);
}

TEST_CASE("line_protocol_parse_3") {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, "test,bar= foo foo=bar");

    CHECK(result == -1);
}

TEST_CASE("line_protocol_parse_4") {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, "test,bar=foo fo o=bar");

    CHECK(result == -1);
}

TEST_CASE("line_protocol_parse_5") {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, ",bar=foo foo=bar");

    CHECK(result == -1);
}
