#include <check.h>
#include <stdarg.h>
#include <stdio.h>

#include "test_hands.h"
#include "test_better.h"
#include "test_utils.h"

int testSuite(Suite * s){
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failed;
}

int main(){
  int failed = 0;

  Suite * hands = testHands();
  Suite * better = testIsBetter();
  Suite * utils = testUtils();

  failed += testSuite(utils);
  failed += testSuite(hands);
  failed += testSuite(better);

  return failed != 0;
}
