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
  ck_assert_int_eq(cs->set[0]->sign,AS);
  ck_assert_int_eq(cs->set_size,1);
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
  ck_assert_int_eq(cs->set[0]->sign,3);
  ck_assert_int_eq(cs->set[1]->sign,3);
  ck_assert_int_eq(cs->set_size,2);
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
  ck_assert_int_eq(cs->set[0]->sign,AS);
  ck_assert_int_eq(cs->set[1]->sign,AS);
  ck_assert_int_eq(cs->set[2]->sign,3);
  ck_assert_int_eq(cs->set[3]->sign,3);
  ck_assert_int_eq(cs->set_size,4);
}
END_TEST

START_TEST(test_brelan)
{
  Card ** c = makeCardsArrayFromArgs(6,
    2,PIQUE,
    3,PIQUE,
    4,COEUR,
    AS,PIQUE,
    AS,COEUR,
    AS,TREFLE
  );
  CardSet * cs = initCardSet(c,6);
  ck_assert_int_eq(cs->type,BRELAN);
  ck_assert_int_eq(cs->set[0]->sign,AS);
  ck_assert_int_eq(cs->set[1]->sign,AS);
  ck_assert_int_eq(cs->set[2]->sign,AS);
  ck_assert_int_eq(cs->set_size,3);
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

  ck_assert_int_eq(cs->set[0]->sign,5);
  ck_assert_int_eq(cs->set[1]->sign,4);
  ck_assert_int_eq(cs->set[2]->sign,3);
  ck_assert_int_eq(cs->set[3]->sign,2);
  ck_assert_int_eq(cs->set[4]->sign,AS);
  ck_assert_int_eq(cs->set_size,5);

}
END_TEST

START_TEST(test_flush2)
{
  Card ** c = makeCardsArrayFromArgs(7,
    2,PIQUE,
    3,COEUR,
    10,PIQUE,
    VALET,COEUR,
    DAME,COEUR,
    ROI,PIQUE,
    AS,PIQUE
  );
  CardSet * cs = initCardSet(c,7);
  ck_assert_int_eq(cs->type,FLUSH);
  ck_assert_int_eq(cs->set[0]->sign,AS);
  ck_assert_int_eq(cs->set[1]->sign,ROI);
  ck_assert_int_eq(cs->set[2]->sign,DAME);
  ck_assert_int_eq(cs->set[3]->sign,VALET);
  ck_assert_int_eq(cs->set[4]->sign,10);
  ck_assert_int_eq(cs->set_size,5);


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
  ck_assert_int_eq(cs->set[0]->sign,AS);
  ck_assert_int_eq(cs->set[1]->sign,VALET);
  ck_assert_int_eq(cs->set[2]->sign,10);
  ck_assert_int_eq(cs->set[3]->sign,9);
  ck_assert_int_eq(cs->set[4]->sign,2);

  ck_assert_int_eq(cs->set[0]->color,PIQUE);
  ck_assert_int_eq(cs->set[1]->color,PIQUE);
  ck_assert_int_eq(cs->set[2]->color,PIQUE);
  ck_assert_int_eq(cs->set[3]->color,PIQUE);
  ck_assert_int_eq(cs->set[4]->color,PIQUE);

}
END_TEST

START_TEST(test_full)
{
  Card ** c = makeCardsArrayFromArgs(8,
    2,PIQUE,
    2,COEUR,
    9,PIQUE,
    9,TREFLE,
    10,PIQUE,
    VALET,COEUR,
    VALET,PIQUE,
    VALET,CARREAU
  );
  CardSet * cs = initCardSet(c,8);
  ck_assert_int_eq(cs->type,FULL);
  ck_assert_int_eq(cs->set[0]->sign,VALET);
  ck_assert_int_eq(cs->set[1]->sign,VALET);
  ck_assert_int_eq(cs->set[2]->sign,VALET);
  ck_assert_int_eq(cs->set[3]->sign,9);
  ck_assert_int_eq(cs->set[4]->sign,9);

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
  ck_assert_int_eq(cs->set[0]->sign,AS);
  ck_assert_int_eq(cs->set[1]->sign,ROI);
  ck_assert_int_eq(cs->set[2]->sign,DAME);
  ck_assert_int_eq(cs->set[3]->sign,VALET);
  ck_assert_int_eq(cs->set[4]->sign,10);


}
END_TEST

Suite* testHands(){
  TCase *tc_core = tcase_create("CoreHands");
  Suite* s = suite_create("TestHands");

//  tcase_add_test(tc_core, none);
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
