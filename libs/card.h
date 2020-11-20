#ifndef __POKer_cards___
#define __POKer_cards___

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#define CARREAU 1
#define COEUR   2
#define TREFLE  3
#define PIQUE   4

typedef uint8_t Color;

#define VALET 11
#define DAME  12
#define ROI   13
#define AS   14

typedef uint8_t Sign;

typedef struct card{
	Sign sign;
	Color color;
}Card;

Card * makeCard(Color c, Sign s);
char * cardToText(Card c);
void destroyCard(Card * c);

#endif
