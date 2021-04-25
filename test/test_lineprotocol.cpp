#include <Arduino.h>
#include <unity.h>

#include <LineProtocol.h>

void test_message_from_arguments_0(void) {
  std::map<String, String> fields = {{"field", "field"}};

  std::map<String, String> tags = {{"tag", "tag"}};

  Message message("measurement", fields, tags, 3);

  TEST_ASSERT_EQUAL_STRING(message.measurement.c_str(), "measurement");
  TEST_ASSERT_EQUAL_STRING(message.fields["field"].c_str(), "field");
  TEST_ASSERT_EQUAL_STRING(message.tags["tag"].c_str(), "tag");
  TEST_ASSERT_EQUAL(message.timestamp, 3);
}

void test_message_from_string_0(void) {
  Message message("measurement foo=bar");

  TEST_ASSERT_EQUAL_STRING(message.measurement.c_str(), "measurement");
}

void test_message_from_string_1(void) {
  Message message("test,bar=foo foo=bar");

  TEST_ASSERT_EQUAL_STRING(message.measurement.c_str(), "test");
  TEST_ASSERT_EQUAL_STRING(message.tags["bar"].c_str(), "foo");
  TEST_ASSERT_EQUAL_STRING(message.fields["foo"].c_str(), "bar");
}

void test_message_from_string_2(void) {
  try {
    Message message("test,bar= foo foo=bar");
    TEST_FAIL();
  } catch (...) {
  };
}

void test_message_from_string_3(void) {
  try {
    Message message("test,bar=foo fo o=bar");
    TEST_FAIL();
  } catch (...) {
  };
}

void test_message_from_string_4(void) {
  try {
    Message message(",bar=foo foo=bar");
    TEST_FAIL();
  } catch (...) {
  };
}

void test_message_validate_0(void) {
  Message message("test,bar=foo foo=bar");

  TEST_ASSERT_EQUAL(0, message.validate({"bar"}, {"foo"}));
  TEST_ASSERT_EQUAL(1, message.validate({"foo"}, {"bar"}));
  TEST_ASSERT_EQUAL(0, message.validate({}, {}));
}

void setup() {
  UNITY_BEGIN();

  RUN_TEST(test_message_from_arguments_0);
  RUN_TEST(test_message_from_string_0);
  RUN_TEST(test_message_from_string_1);
  RUN_TEST(test_message_from_string_2);
  RUN_TEST(test_message_from_string_3);
  RUN_TEST(test_message_from_string_4);

  RUN_TEST(test_message_validate_0);
}

void loop() { UNITY_END(); }

int main() {
  setup();
  loop();

  return 0;
}
