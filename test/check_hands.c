#include <check.h>
#include <stdarg.h>
#include <stdio.h>

#include "game.h"
#include "hands.h"

Card ** makeCardsArrayFromArgs(int n_cards,...){
  va_list cards_args;
  va_start(cards_args,n_cards);

  Card ** hand = malloc(sizeof(Card*)*(n_cards));

  for (int i=0;i<n_cards;i++)
  {
    int sign=(int) va_arg(cards_args,int);
    int color=(int) va_arg(cards_args,int);
    hand[i]=makeCard(color,sign);
  }
  return hand;
}

START_TEST(test_pair)
{
  Card ** c = makeCardsArrayFromArgs(3,
    AS,PIQUE,
    3,COEUR,
    3,CARREAU
  );
  ck_assert_int_eq(1,findPaire(c,3));
}
END_TEST


START_TEST(test_flush)
{
  Card ** c = makeCardsArrayFromArgs(7,
    AS,PIQUE,
    2,PIQUE,
    3,COEUR,
    3,CARREAU,
    3,PIQUE,
    4,PIQUE,
    5,PIQUE
  );
  ck_assert_int_eq(5,findFlush(c,1));
}
END_TEST

START_TEST(test_double_pair)
{
  Card ** c = makeCardsArrayFromArgs(5,
    AS,PIQUE,
    2,PIQUE,
    3,PIQUE,
    AS,PIQUE,
    3,COEUR
  );
  ck_assert_int_eq(5,findDoublePaireHighest(c,7));
}
END_TEST


Suite* testHands(){
  TCase *tc_core = tcase_create("Core");
  Suite* s = suite_create("TestHands");

  tcase_add_test(tc_core, test_pair);
  tcase_add_test(tc_core, test_double_pair);
  tcase_add_test(tc_core, test_flush);
  suite_add_tcase(s, tc_core);
  return s;
}

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
