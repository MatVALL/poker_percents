#ifndef games___poker__
#define games___poker__

#include "card.h"
#include<time.h>
#include<stdbool.h>

#define HANDSIZE 2
#define DECKSIZE 52

//represente la situation du jeu.
typedef struct game{
	Card ** hand;
	Card ** drawn;
	int n_drawn;
}Game;

Game * makeGame(char * path);
void destroyGame(Game * g);
void sortHand(Card ** cards, int length);
#endif
