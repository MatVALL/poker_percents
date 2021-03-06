#ifndef __POKER_cards___
#define __POKER_cards___

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

typedef enum color{CARREAU,COEUR,TREFLE,PIQUE} Color;
typedef enum sign{VALET=11,DAME=12,ROI=13,AS=14} Sign;

typedef struct card{
	Sign sign;
	Color color;
}Card;

Card * makeCard(Color c, Sign s);
void printCard(Card c);
void destroyCard(Card * c);

#endif
