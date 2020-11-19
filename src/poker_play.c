#include <stdio.h>
#include <sys/time.h>
#include "game.h"

//TODO make the srand depend of the pid
void initRand(){
	struct timeval time;
	gettimeofday(&time,NULL);
	srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int main(void){
	initRand();
	for (int i = 0 ; i < 1 ; i ++){
		Game * g = makeGame();
		printf("hand:");
		printf("\t\t%s %s\n",cardToText(*g->hand[0]),cardToText(*g->hand[1]));

		printf("first draw:");
		printf("\t%s %s %s\n",cardToText(*g->deck[0]),cardToText(*g->deck[1]),cardToText(*g->deck[2]));

		printf("second draw:");
		printf("\t%s\n",cardToText(*g->deck[3]));

		printf("third draw:");
		printf("\t%s\n",cardToText(*g->deck[4]));

		isBetter(g->hand,g->hand,g->deck,5);
		destroyGame(g);
	}
	return 0;
}
