#include <stdio.h>
#include <stdlib.h>
#include <twx/twx.h>
#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

void test_twx_parse_to_json() {
  char test_class_names[] =
      "bg-red-500 border-2 p-2 w-2 dark:sm:bg-green-500 "
      "dark:bg-neutral-950 dark:p-4 hover:bg-green-400 lg:dark:p-12";
  printf("parsing: %s\n", test_class_names);
  char *json = twx_parse_to_json(test_class_names);
  printf("%s\n", json);
  free(json);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_twx_parse_to_json);
  return UNITY_END();
}
