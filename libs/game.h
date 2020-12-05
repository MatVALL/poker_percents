#ifndef games___poker__
#define games___poker__

#include "card.h"
#include<time.h>
#include<stdbool.h>

#define HANDSIZE 2
#define DECKSIZE 52

typedef struct game{
	Card * hand[HANDSIZE];
	Card * deck[DECKSIZE-HANDSIZE];
}Game;

Game * makeGame();
void destroyGame(Game * g);
int isBetter(Card * hand1[2],Card * hand2[2],Card ** deck,int cards_drawn);
void sortHand(Card ** cards, int length);
#endif
