#include "test_hands.h"

Card ** makeCardsArrayFromArgs(int n_cards,...){
  Card ** hand = malloc(sizeof(Card*)*(n_cards));

  va_list cards_args;
  va_start(cards_args,n_cards);
  for (int i=0;i<n_cards;i++)
  {
    int sign=(int) va_arg(cards_args,int);
    int color=(int) va_arg(cards_args,int);
    hand[i]=makeCard(color,sign);
  }
  return hand;
}

START_TEST(none)
{
  Card ** c = makeCardsArrayFromArgs(5,
    AS,PIQUE,
    3,CARREAU,
    2,COEUR,
    5,PIQUE,
    VALET,COEUR
  );
  CardSet * cs = initCardSet(c,5);
  ck_assert_int_eq(cs->type,SINGLE);
}
END_TEST

START_TEST(test_pair)
{
  Card ** c = makeCardsArrayFromArgs(3,
    AS,PIQUE,
    3,COEUR,
    3,CARREAU
  );
  CardSet * cs = initCardSet(c,3);
  ck_assert_int_eq(cs->type,PAIR);
}
END_TEST

START_TEST(test_double_pair)
{
  Card ** c = makeCardsArrayFromArgs(5,
    2,PIQUE,
    3,PIQUE,
    3,COEUR,
    AS,PIQUE,
    AS,PIQUE
  );
  CardSet * cs = initCardSet(c,5);
  ck_assert_int_eq(cs->type,DOUBLE);
}
END_TEST

START_TEST(test_brelan)
{
  Card ** c = makeCardsArrayFromArgs(6,
    2,PIQUE,
    3,PIQUE,
    3,COEUR,
    AS,PIQUE,
    AS,COEUR,
    AS,TREFLE
  );
  CardSet * cs = initCardSet(c,5);
  ck_assert_int_eq(cs->type,BRELAN);
}
END_TEST

START_TEST(test_flush)
{
  Card ** c = makeCardsArrayFromArgs(7,
    2,PIQUE,
    3,COEUR,
    3,CARREAU,
    3,PIQUE,
    4,PIQUE,
    5,TREFLE,
    AS,PIQUE
  );
  CardSet * cs = initCardSet(c,7);
  ck_assert_int_eq(cs->type,FLUSH);
}
END_TEST

START_TEST(test_flush2)
{
  Card ** c = makeCardsArrayFromArgs(7,
    2,PIQUE,
    3,COEUR,
    10,PIQUE,
    VALET,PIQUE,
    DAME,PIQUE,
    ROI,PIQUE,
    AS,PIQUE
  );
  CardSet * cs = initCardSet(c,7);
  ck_assert_int_eq(cs->type,FLUSH);
}
END_TEST

START_TEST(test_color)
{
  Card ** c = makeCardsArrayFromArgs(7,
    2,PIQUE,
    3,COEUR,
    9,PIQUE,
    10,PIQUE,
    VALET,PIQUE,
    ROI,TREFLE,
    AS,PIQUE
  );
  CardSet * cs = initCardSet(c,7);
  ck_assert_int_eq(cs->type,COLOR);
}
END_TEST

START_TEST(test_full)
{
  Card ** c = makeCardsArrayFromArgs(7,
    2,PIQUE,
    2,COEUR,
    9,PIQUE,
    10,PIQUE,
    VALET,COEUR,
    VALET,PIQUE,
    VALET,CARREAU
  );
  CardSet * cs = initCardSet(c,7);
  ck_assert_int_eq(cs->type,FULL);
}
END_TEST

START_TEST(test_colored_flush)
{
  Card ** c = makeCardsArrayFromArgs(7,
    2,PIQUE,
    3,COEUR,
    10,PIQUE,
    VALET,PIQUE,
    DAME,PIQUE,
    ROI,PIQUE,
    AS,PIQUE
  );
  CardSet * cs = initCardSet(c,7);
  ck_assert_int_eq(cs->type,COLORED);

}
END_TEST

Suite* testHands(){
  TCase *tc_core = tcase_create("CoreHands");
  Suite* s = suite_create("TestHands");

//  tcase_add_test(tc_core, none);
//  tcase_add_test(tc_core, test_pair);
  tcase_add_test(tc_core, test_double_pair);
/*  tcase_add_test(tc_core, test_brelan);
  tcase_add_test(tc_core, test_flush);
  tcase_add_test(tc_core, test_flush2);
  tcase_add_test(tc_core, test_color);
  tcase_add_test(tc_core, test_full);
  tcase_add_test(tc_core, test_colored_flush);
*/
  suite_add_tcase(s, tc_core);
  return s;
}
