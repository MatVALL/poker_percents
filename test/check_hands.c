#include <check.h>
#include <stdio.h>

START_TEST(test_import)
{
  ck_assert_int_eq(0,1);
}
END_TEST

Suite* testNothing(){
  TCase *tc_core = tcase_create("Core");
  Suite* s = suite_create("Nothing");

  tcase_add_test(tc_core, test_import);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(){
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = testNothing();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? 0 : 1;
}
