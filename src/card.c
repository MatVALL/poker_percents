#include "card.h"
/**
	create a card object from a sign and a color
	makes a malloc
**/
Card * makeCard(Color c, Sign s){
	Card * card = (Card*)malloc(sizeof(Card));
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
/** Returns a string containing the text from a card
	Malloc is made on the string, so free it when it is over
**/
char * cardToText(Card c){
	char sign[3];
	char color[3];
	switch (c.color){
		case COEUR:
			sprintf(color,"<3");break;
		case PIQUE:
			sprintf(color,"->");break;
		case TREFLE:
			sprintf(color,"-3");break;
		case CARREAU:
			sprintf(color,"<>");break;
		default:
			sprintf(color,"??");
	};

	switch (c.sign){
		case VALET:
			sprintf(sign,"V");break;
		case DAME:
			sprintf(sign,"D");break;
		case ROI:
			sprintf(sign,"R");break;
		case AS:
			sprintf(sign,"A");break;
		default:
			sprintf(sign,"%d",c.sign);
	};
	char* text=(char*)malloc(sizeof(char)*5);
	sprintf(text,"%s%s",sign,color);
	return text;
}
