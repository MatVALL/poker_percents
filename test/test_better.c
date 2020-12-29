#include "test_better.h"
#include "test_hands.h"
#include "best.h"

START_TEST(test1)
{
  Card ** hand1 = makeCardsArrayFromArgs(2,
    2,PIQUE,
    3,COEUR
  );
  Card ** hand2 = makeCardsArrayFromArgs(2,
    2,PIQUE,
    3,COEUR
  );
  Card ** drawn = makeCardsArrayFromArgs(3,
    2,PIQUE,
    3,COEUR,
    4,TREFLE
  );
	Card** h1 = concatCards(hand1,2,drawn,3);
  Card** h2 = concatCards(hand2,2,drawn,3);
  ck_assert_int_eq(0,isBetter(h1,h2,5));
  ck_assert_int_eq(isBetter(h1,h2,5),-isBetter(h2,h1,5));
}
END_TEST

Suite* testIsBetter(void){
  TCase *tc_core = tcase_create("CoreIsBetter");
  Suite* s = suite_create("TestBetter");
  tcase_add_test(tc_core, test1);
  suite_add_tcase(s, tc_core);
  return s;
}
