#include <Arduino.h>
#include <unity.h>

#include <LineProtocol.h>


void test_line_protocol_parse_0(void) {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, "measurement foo=bar");

    TEST_ASSERT_EQUAL(result, 0);
    TEST_ASSERT_EQUAL("measurement", lp.measurement);
}

void test_line_protocol_parse_1(void) {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, "test foo=bar");

    TEST_ASSERT_EQUAL(result, 0);
    TEST_ASSERT_EQUAL("test", lp.measurement);
}

void test_line_protocol_parse_2(void) {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, "test,bar=foo foo=bar");

    TEST_ASSERT_EQUAL(result, 0);
    TEST_ASSERT_EQUAL("test", lp.measurement);
    TEST_ASSERT_EQUAL("foo",  lp.tags["bar"]);
    TEST_ASSERT_EQUAL("bar", lp.fields["foo"]);
}

void test_line_protocol_parse_3(void) {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, "test,bar= foo foo=bar");

    TEST_ASSERT_EQUAL(result, -1);
}

void test_line_protocol_parse_4(void) {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, "test,bar=foo fo o=bar");

    TEST_ASSERT_EQUAL(result, -1);
}

void test_line_protocol_parse_5(void) {
    struct line_protocol lp;
    int result; 

    result = line_protocol_parse(lp, ",bar=foo foo=bar");

    TEST_ASSERT_EQUAL(result, -1);
}

void setup() {
    delay(2000);

    UNITY_BEGIN();

    RUN_TEST(test_line_protocol_parse_0);
    RUN_TEST(test_line_protocol_parse_1);
    RUN_TEST(test_line_protocol_parse_2);
    RUN_TEST(test_line_protocol_parse_3);
    RUN_TEST(test_line_protocol_parse_4);
    RUN_TEST(test_line_protocol_parse_5);

    UNITY_END();
}
