#include <check.h>
#include <stdarg.h>
#include <stdio.h>

#include "game.h"
#include "hands.h"

Suite* testHands();
Card ** makeCardsArrayFromArgs(int n_cards,...);
