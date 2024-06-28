#include <stdio.h>
#include <twx/twx.h>
#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

void test_twx_parse_to_json() {
  char test_class_names[] = "bg-red-500 p-2 dark:bg-neutral-950 dark:p-4";
  printf("parsing: %s\n", test_class_names);
  const char *json = twx_parse_to_json(test_class_names);
  printf("%s\n", json);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_twx_parse_to_json);
  return UNITY_END();
}
