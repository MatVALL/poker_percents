#include "game.h"
#include "hands.h"

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

/**
	turn game in card array
**/
Card **  getTotalCards(Game * g,int cards_drawn){
  Card ** fullhand1 = malloc(sizeof(Card*)*(2+cards_drawn));
  fullhand1[0]= g->hand[0];
  fullhand1[1]= g->hand[1];

  for (int i = 0; i < cards_drawn; i ++){
    fullhand1[i+2] = g->deck[i];
  }
  sortHand(fullhand1,2+cards_drawn);
  return fullhand1;
}

/**
	returns 1 if the hand1 is better, -1 if it is not and 0 if it is a draw
**/
int isBetter(Card * hand1[2],Card * hand2[2],Card ** drawn,int cards_drawn){
	Card ** fullhand1 = malloc(sizeof(Card*)*(2+cards_drawn));
	Card ** fullhand2 = malloc(sizeof(Card*)*(2+cards_drawn));
	fullhand1[0]= hand1[0]; fullhand1[1]= hand1[1];
	fullhand2[0]= hand2[0]; fullhand2[1]= hand2[1];

	for (int i = 0; i < cards_drawn; i ++){
		fullhand1[i+2] = drawn[i];
		fullhand2[i+2] = drawn[i];
	}
	sortHand(fullhand1,2+cards_drawn);
	sortHand(fullhand2,2+cards_drawn);
	int length=2+cards_drawn;
	
	int (*comparated_functions[9])(Card ** hand,int length) = {
		*findColoredFlush,
		*findFullBrelan,
		*findFullPaire,
		*findColor,
		*findFlush,
		*findBrelan,
		*findDoublePaireSecond,
		*findDoublePaireHighest,
		*findPaire
	};
	for (int i=0; i < 9;i++){
		int (*func)(Card ** hand,int length) = comparated_functions[i];
		printf("%d %d\n",func(fullhand1,length),func(fullhand2,length));
		if(func(fullhand1,length)>=0 && func(fullhand2,length)<0)
			return 1;
		if(func(fullhand2,length)>=0 && func(fullhand1,length)<0)
			return -1;
		if(func(fullhand2,length)>=0 && func(fullhand1,length)>=0)
			return 1000;
	}
	return 0;
}

/**
	create a game struct (destroy it !!)
**/
Game *  makeGame(){
	Card* cards[52];
	int ind = 0;
	for (int sign = 2; sign <= AS; sign ++){
		for (int color = 0; color < 4; color ++){
			cards[ind++] = makeCard(color,sign);
		}
	}
	shuffleDeck(cards,52);

	Game *  g = (Game*)malloc(sizeof(Game));
	for (int card =0; card < 2;card ++)
		g->hand[card]=cards[card];
	for (int card =0; card < 50;card ++)
		g->deck[card]=cards[card+2];
	return g;
}

void destroyGame(Game * g){
	for (int i = 0; i <2; i ++){
		destroyCard(g->hand[i]);
	}
	for (int i = 0; i <50; i ++){
		destroyCard(g->deck[i]);
	}
	free(g);
}
