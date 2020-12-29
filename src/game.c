#include "game.h"
#include "hands.h"

/** sort by sign
	tri pas opti mais 7 cartes max.**/
void sortHand(Card ** cards, int length){
	for (int i =0; i < length-1 ; i++){
		int max_ind=i;
		for (int card = i+1; card < length; card ++){
			max_ind = cards[card]->sign>cards[max_ind]->sign?card:max_ind;
			if (cards[card]->sign==1)
				max_ind = card;
		}
		Card*tmp = cards[i];
		cards[i] =cards[max_ind];
		cards[max_ind]=tmp;
	}
}

/** shuffle the set of cards of length length
*/
void shuffleDeck(Card ** cards, int length){
	for (int ind=0;ind<length;ind ++){
		int random_ind = ind + rand()%(length-ind);
		Card * tmp =cards[ind];
		cards[ind]=cards[random_ind];
		cards[random_ind] = tmp;
	}
}

Color getColor(char c){
	switch(c){
		case '%': return TREFLE;
		case '<': return COEUR;
		case '>': return PIQUE;
		case '#': return CARREAU;
		default : return -1;
	}
}


/**
	create a game from argc/argv (the process input)
**/
Game *  makeGame(char * path){
//	Card** cards =  makeDeck();
	Game * g = malloc(sizeof(Game));
	if(g==NULL)
	{
		perror("malloc");
		exit(1);
	}
	g->hand = malloc(sizeof(Card*)*HANDSIZE);
	g->drawn = malloc(sizeof(Card*)*5);
	if(g->hand==NULL||g->drawn==NULL)
	{
		perror("malloc");
		exit(1);
	}
	g->n_drawn=0;
	//read hand
	char line[10000];
	FILE * f;
	if(!(f=fopen(path,"r"))){
		perror("fopen");
		exit(1);
	}
	int nread = 2;//
	while(fgets(line,10000,f)){
		if(line[0]=='#')
			continue;
		int sign1, sign2, sign3;
		char c1, c2, c3;
		if(nread==2 && sscanf(line,"%d%c %d%c",&sign1,&c1,&sign2,&c2)>=2){
			g->hand[0]=makeCard(getColor(c1),sign1==1?14:sign1);
			g->hand[1]=makeCard(getColor(c2),sign2==1?14:sign1);
			nread=3;
		}
		else if(nread==3 && sscanf(line,"%d%c %d%c %d%c",&sign1,&c1,&sign2,&c2,&sign3,&c3)>=6){
			g->drawn[0]=makeCard(getColor(c1),sign1==1?14:sign1);
			g->drawn[1]=makeCard(getColor(c2),sign2==1?14:sign2);
			g->drawn[2]=makeCard(getColor(c3),sign3==1?14:sign3);
			g->n_drawn=3;
			nread=1;
		}
		else if(nread==1&&sscanf(line,"%d%c",&sign1,&c1)>=2){
			g->drawn[g->n_drawn++]=makeCard(getColor(c1),sign1==1?14:sign1);
		}
	}
	return g;
}
/*
	destroy every card in the game, and free the memory.
*/
void destroyGame(Game * g){
	for (int i = 0; i <2; i ++){
		destroyCard(g->hand[i]);
	}
	for (int i = 0; i <g->n_drawn; i ++){
		destroyCard(g->drawn[i]);
	}
	free(g->drawn);
	free(g->hand);
	free(g);
}
