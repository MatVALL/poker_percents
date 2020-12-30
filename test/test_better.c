#include "test_better.h"
#include "test_hands.h"
#include "best.h"

START_TEST(test_same)
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

START_TEST(test_square_flush)
{
  Card ** hand1 = makeCardsArrayFromArgs(2,
    AS,PIQUE,
    3,COEUR
  );
  Card ** hand2 = makeCardsArrayFromArgs(2,
    ROI,PIQUE,
    ROI,COEUR
  );
  Card ** drawn = makeCardsArrayFromArgs(5,
    ROI,CARREAU,
    2,PIQUE,
    5,COEUR,
    4,TREFLE,
    ROI,TREFLE
  );
	Card** h1 = concatCards(hand1,2,drawn,3);
  Card** h2 = concatCards(hand2,2,drawn,3);
  ck_assert(isBetter(h1,h2,5)<0);
  ck_assert_int_eq(isBetter(h1,h2,5),-isBetter(h2,h1,5));

  h1 = concatCards(hand1,2,drawn,4);
  h2 = concatCards(hand2,2,drawn,4);
  ck_assert(isBetter(h1,h2,6)>0);
  ck_assert_int_eq(isBetter(h1,h2,6),-isBetter(h2,h1,6));

  h1 = concatCards(hand1,2,drawn,5);
  h2 = concatCards(hand2,2,drawn,5);
  ck_assert(isBetter(h1,h2,7)<0);
  ck_assert_int_eq(isBetter(h1,h2,7),-isBetter(h2,h1,7));
}
END_TEST

START_TEST(test_compare_remaining)
{
  Card ** hand1 = makeCardsArrayFromArgs(2,
    ROI,PIQUE,
    DAME,COEUR
  );
  Card ** hand2 = makeCardsArrayFromArgs(2,
    ROI,COEUR,
    2,PIQUE
  );
  Card ** drawn = makeCardsArrayFromArgs(5,
    ROI,CARREAU,
    4,TREFLE,
    ROI,TREFLE
  );
	Card** h1 = concatCards(hand1,2,drawn,3);
  Card** h2 = concatCards(hand2,2,drawn,3);
  ck_assert(isBetter(h1,h2,5)>0);
  ck_assert_int_eq(isBetter(h1,h2,5),-isBetter(h2,h1,5));
}
END_TEST

Suite* testIsBetter(void){
  TCase *tc_core = tcase_create("CoreIsBetter");
  Suite* s = suite_create("TestBetter");
  tcase_add_test(tc_core, test_same);
  tcase_add_test(tc_core, test_square_flush);
    tcase_add_test(tc_core, test_compare_remaining);
  suite_add_tcase(s, tc_core);
  return s;
}
