#include "../src/LineProtocol.h"
#include "catch/catch.hpp"

#include <stdio.h>
#include <stdlib.h>


TEST_CASE("line_protocol_parse_0") {
    struct line_protocol lp;
    int result; 

    memset(&lp, '\0', sizeof(struct line_protocol));
    
    result = line_protocol_parse(lp, "measurement foo=bar");

    printf("%d %s\n", result, lp.measurement);

    CHECK(result == 0);
    CHECK(strcmp("measurement", lp.measurement) == 0);
}

TEST_CASE("line_protocol_parse_1") {
    struct line_protocol lp;
    int result; 

    memset(&lp, '\0', sizeof(struct line_protocol));
    
    result = line_protocol_parse(lp, "test foo=bar");

    printf("%d %s\n", result, lp.measurement);

    CHECK(result == 0);
    CHECK(strcmp("test", lp.measurement) == 0);
}

TEST_CASE("line_protocol_parse_2") {
    struct line_protocol lp;
    int result; 

    memset(&lp, '\0', sizeof(struct line_protocol));
    
    result = line_protocol_parse(lp, "test,bar=foo foo=bar");

    printf("%d %s\n", result, lp.measurement);

    CHECK(result == 0);
    CHECK(strcmp("test", lp.measurement) == 0);
}
