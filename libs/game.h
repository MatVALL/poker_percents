#include "card.h"
#include<time.h>
#include<stdbool.h>

typedef struct game{
	Card * hand[2];
	Card * deck[50];
}Game;

Game * makeGame();
void destroyGame(Game * g);
int isBetter(Card * hand1[2],Card * hand2[2],Card ** deck,int cards_drawn);
