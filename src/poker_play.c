#include <stdio.h>
#include <sys/time.h>
#include "game.h"
#include "best.h"

//TODO make the srand depend of the pid
void initRand(){
	struct timeval time;
	gettimeofday(&time,NULL);
	srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//memory leak : free cardToText
void printGame(Game * g){
	printf("hand:\n");
	printCard(*g->hand[0]);printCard(*g->hand[1]);
	for(int i=0;i<g->n_drawn;i++){
		printCard(*(g->drawn[i]));
	}
}

/**
	return true if the card given is in the hand or has been drawn
	return false otherwise
**/
int cardIsInGame(Card * c, Game * g){
	for(int i=0;i<g->n_drawn;i++){
		if(g->drawn[i]->sign==c->sign && g->drawn[i]->color==c->color)
			return 1;
	}
	if(g->n_drawn>0&&  g->drawn[0]->sign==c->sign && g->drawn[0]->color==c->color)
		return 1;
	if(g->n_drawn>1&& g->drawn[1]->sign==c->sign && g->drawn[1]->color==c->color)
		return 1;
	return 0;
}

double getProba(Game * g){
	int n_parties_jouees = 0;
	int n_gagnees = 0;

	Card** game_hand = concatCards(g->hand,2,g->drawn,g->n_drawn);
	sortHand(game_hand,2+g->n_drawn);

	for(int i = 0; i < 52; i++){
		for(int j = 0; j < 52; j++){
			Color c1 = i%4;
			Color c2 = j%4;
			Sign s1 = (i/4)+2;
			Sign s2 = (j/4)+2;

			Card * card1 = makeCard(c1, s1);
			Card * card2 = makeCard(c2, s2);
			Card ** hand = malloc(sizeof(Card*)*2);

			if(hand==NULL){
				perror("malloc");
				exit(1);
			}
			hand[0]=card1;
			hand[1]=card2;

			Card** simulated_hand = concatCards(hand,2,g->drawn,g->n_drawn);
			sortHand(simulated_hand,2+g->n_drawn);

			if(!cardIsInGame(card1,g)&& !cardIsInGame(card2,g)){
				n_parties_jouees++;
				if(isBetter(game_hand,simulated_hand,2+g->n_drawn)>0){
					n_gagnees++;
				}
				else{
					printf("BETTER HAND :");
					printCard(*card1);
					printCard(*card2);
					printf("\n");
				}
			}
			free(simulated_hand);
			free(hand);
			destroyCard(card1);
			destroyCard(card2);
		}
	}
	free(game_hand);
	return (double)n_gagnees/n_parties_jouees;
}

int main(int argc, char**argv){
	if(argc<2){
		fprintf(stderr, "Usage : ./poker_play game_file\n");
		exit(0);
	}
	printf("creating game\n");
	Game * g = makeGame(argv[1]);

	printf("calculating ...\n");
	printf("proba : %lf\n",getProba(g));
	printf("done.\n");
	destroyGame(g);
	return 0;
}
