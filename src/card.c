#include "card.h"
/**
	create a card object from a sign and a color
	makes a malloc
**/
Card * makeCard(Color c, Sign s){
	Card * card = malloc(sizeof(Card));
	if(card==NULL)
	{
		perror("malloc");
		exit(1);
	}
	card->sign = s;
	card->color = c;
	return card;
}
/**
	free the memory allocated when a card object is created
**/
void destroyCard(Card * c){
	free(c);
}

void printCard(Card c){
	switch (c.color){
		case COEUR:
			printf("<3");break;
		case PIQUE:
			printf("->");break;
		case TREFLE:
			printf("-3");break;
		case CARREAU:
			printf("<>");break;
		default:
			printf("??");
	};

	switch (c.sign){
		case VALET:
			printf("V");break;
		case DAME:
			printf("D");break;
		case ROI:
			printf("R");break;
		case AS:
			printf("A");break;
		default:
			printf("%d",c.sign);
	};
}
