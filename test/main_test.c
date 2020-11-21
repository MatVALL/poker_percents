#include <check.h>
#include <stdarg.h>
#include <stdio.h>

#include "test_hands.h"

int main(){
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = testHands();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return no_failed != 0;
}
