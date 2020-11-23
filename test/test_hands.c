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
  Card ** c = makeCardsArrayFromArgs(3,
    AS,PIQUE,
    3,CARREAU,
    2,COEUR,
    5,PIQUE,
    VALET,COEUR
  );
  ck_assert_int_eq(-1,findPaire(c,5));
  ck_assert_int_eq(-1,findDoublePaireSecond(c,5));
  ck_assert_int_eq(-1,findDoublePaireHighest(c,5));
  ck_assert_int_eq(-1,findPaire(c,5));
  ck_assert_int_eq(-1,findBrelan(c,5));
  ck_assert_int_eq(-1,findFlush(c,5));
  ck_assert_int_eq(-1,findColor(c,5));
  ck_assert_int_eq(-1,findFullPaire(c,5));
  ck_assert_int_eq(-1,findFullBrelan(c,5));
  ck_assert_int_eq(-1,findColoredFlush(c,5));

}
END_TEST

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

START_TEST(test_double_pair)
{
  Card ** c = makeCardsArrayFromArgs(5,
    2,PIQUE,
    3,PIQUE,
    3,COEUR,
    AS,PIQUE,
    AS,PIQUE
  );
  ck_assert_int_eq(3,findDoublePaireHighest(c,5));
  ck_assert_int_eq(1,findDoublePaireSecond(c,5));
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
  ck_assert_int_eq(3,findBrelan(c,6));

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
  ck_assert_int_eq(0,findFlush(c,1));
}
END_TEST

START_TEST(test_flush2)
{
  Card ** c = makeCardsArrayFromArgs(7,
    2,PIQUE,
    3,COEUR,
    9,PIQUE,
    10,PIQUE,
    VALET,PIQUE,
    ROI,PIQUE,
    AS,PIQUE
  );
  ck_assert_int_eq(2,findFlush(c,7));
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
  ck_assert_int_eq(0,findColor(c,7));
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
  ck_assert_int_eq(0,findFullPaire(c,7));
  ck_assert_int_eq(4,findFullBrelan(c,7));
}
END_TEST

START_TEST(test_colored_flush)
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
  ck_assert_int_eq(0,findColoredFlush(c,7));
}
END_TEST

Suite* testHands(){
  TCase *tc_core = tcase_create("Core");
  Suite* s = suite_create("TestHands");

  tcase_add_test(tc_core, none);
  tcase_add_test(tc_core, test_pair);
  tcase_add_test(tc_core, test_double_pair);
  tcase_add_test(tc_core, test_brelan);
  tcase_add_test(tc_core, test_flush);
  tcase_add_test(tc_core, test_flush2);
  tcase_add_test(tc_core, test_color);
  tcase_add_test(tc_core, test_full);
  tcase_add_test(tc_core, test_colored_flush);

  suite_add_tcase(s, tc_core);
  return s;
}
