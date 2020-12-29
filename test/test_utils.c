#include "test_utils.h"

START_TEST(test_add_to_set_from_first)
{
  Card ** hand1 = makeCardsArrayFromArgs(4,
    2,PIQUE,
    3,COEUR,
    4,CARREAU,
    5,TREFLE
  );
  CardSet * cs = makeCardSet(hand1,4);
  for(int i=0;i<4;i++){
    addCardToSet(cs,hand1[i]);
  }
  ck_assert_int_eq(cs->total_size-cs->set_size,0);
  ck_assert_int_eq(cs->set_size,4);
}
END_TEST

START_TEST(test_add_to_set_from_last)
{
  Card ** hand1 = makeCardsArrayFromArgs(4,
    2,PIQUE,
    3,COEUR,
    4,CARREAU,
    5,TREFLE
  );
  CardSet * cs = makeCardSet(hand1,4);
  for(int i=3;i>=0;i--){
    addCardToSet(cs,hand1[i]);
  }
}
END_TEST

Suite* testUtils(void){
  TCase *tc_core = tcase_create("CoreUtils");
  Suite* s = suite_create("TestUtils");

  tcase_add_test(tc_core, test_add_to_set_from_first);
  tcase_add_test(tc_core, test_add_to_set_from_last);

  suite_add_tcase(s, tc_core);
  return s;
}
