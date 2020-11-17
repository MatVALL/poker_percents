#include "game.h"

/** sort by sign
	tri pas opti mais 7 cartes max donc osef**/
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

void shuffleDeck(Card ** cards, int length){
	Card* cards_shuffled[52];
	for (int ind=0;ind<length;ind ++){
		int random_ind = ind + rand()%(length-ind);
		Card * tmp =cards[ind];
		cards[ind]=cards[random_ind];
		cards[random_ind] = tmp;
	}
}


/**
	/!\ the hand is supposed to be sorted by sign (valeur)
**/

int isQuinteFlush(Card ** hand,int length){
	return 0;
}
int isCarre(Card ** hand,int length){
	return 0;
}
int isFull(Card ** hand,int length){
	return 0;
}
int isColor(Card ** hand,int length){
	return 0;
}
int isSuite(Card ** hand,int length){
	int suite_length=0;
	for (int i = 0; i < length; i ++){
		if(hand[i]->sign ==hand[i+1]->sign)
			continue;
		else if(hand[i]->sign ==hand[i+1]->sign+1){
			suite_length++;
			if (suite_length >=5)
				return 1;
		}
		else{
			suite_length=0;
		}
	}
	return 0;
}

int findBrelan(Card ** hand,int length){
	for (int i = 0 ; i < length-2 ; i++)
		if(hand[i]->sign ==hand[i+1]->sign && hand[i]->sign ==hand[i+2]->sign)
			return i;
	return -1;
}

/*
	return the first index of a paire
	returns -1 if not found
*/
int findPaire(Card ** hand,int length){
	for (int i = 0 ; i < length-1 ; i++)
		if(hand[i]->sign ==hand[i+1]->sign)
			return i;
	return -1;
}

int findDoublePaire(Card ** hand,int length){
	int pairOne = findPaire(hand,length);
	if(pairOne<0)
		return -1;
	int pairTwo = findPaire(hand+pairOne+2,length - pairOne-2);
	if(pairTwo<0)
		return -1;
	return 1;
}

/**
	returns 1 if the hand1 is better, -1 if it is not and 0 if it is a draw
**/
int isBetter(Card * hand1[2],Card * hand2[2],Card ** deck,int cards_drawn){
	Card ** fullhand1 = malloc(sizeof(Card*)*(2+cards_drawn));
	fullhand1[0]= hand1[0]; fullhand1[1]= hand1[1];

	for (int i = 0; i < cards_drawn; i ++){
		fullhand1[i+2] = deck[i];
	}

	sortHand(fullhand1,2+cards_drawn);
	for (int i = 0; i < 2+cards_drawn; i ++){
		printf("%s ",cardToText(*fullhand1[i]));
	}
	printf("\n%d ",findPaire(fullhand1,7));
	printf("%d ",findDoublePaire(fullhand1,7));
	printf("%d\n",findBrelan(fullhand1,7));
	return 0;
}


Game *  makeGame(){
	Card* cards[52];
	int ind = 0;
	for (int sign = 2; sign <= AS; sign ++){
		for (int color = 1; color <= 4; color ++){
			cards[ind++] = makeCard(color,sign);
		}
	}
	shuffleDeck(cards,52);

	Game *  g = (Game*)malloc(sizeof(Game));
	for (int card =0; card < 2;card ++)
		g->hand[card]=cards[card];
	for (int card =0; card < 50;card ++)
		g->hand[card]=cards[card+2];
	return g;
}

void destroyGame(Game * g){
//TODO
}
