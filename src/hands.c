#include "hands.h"
//TODO: BUG si cartes semblables pour la suite
//TODO: BUG si AS-2 pour la suite !!!
/*
	return the index of the biggest paire
	returns -1 if not found
*/
int findPaire(Card ** hand,int length){
	for (int i = length-2 ; i >=0  ;i --){
		if (hand[i]->sign == hand[i+1]->sign)
			return i+1;
		}
	return -1;
}

/*return the index of the biggest paire
  returns -1
*/
int findDoublePaireHighest(Card ** hand,int length){
	int first_pair  = findPaire(hand,length);
	for (int i = length-2 ; i >=0  ;i --){
		if (hand[i]->sign == hand[i+1]->sign){
			if (first_pair >= 0)
				return first_pair;
		}
	}
	return -1;
}

/*return the index of the 2nd biggest paire
  returns -1
*/
int findDoublePaireSecond(Card ** hand,int length){
	int first_pair  = findPaire(hand,length);
	for (int i = first_pair-2 ; i >=0  ;i --){
		if (hand[i]->sign == hand[i+1]->sign){
			if (first_pair >= 0)
				return i+1;
		}
	}
	return -1;
}

/*
  retourne la position de la carte au debut du plus grand brelan trouvé
	returns -1 if not found
*/
int findBrelan(Card ** hand,int length){
	for (int i = length-3 ; i >=0  ;i --){
		if (hand[i]->sign == hand[i+1]->sign && hand[i+1]->sign == hand[i+2]->sign)
			return i;
	}
	return -1;
}

/*
	returns the index of the highest card in a flush
	returns -1 if not found
*/
int findFlush(Card ** hand,int length){
	int flush_length=1;
	int highest_id = length - 1;
	for (int i = length-2 ; i >=0  ;i --)
	{

		if (hand[i]->sign == hand[i+1]->sign)
		{
			continue;
		}
		if (hand[i]->sign+1 == hand[i+1]->sign)
		{
			flush_length ++;
			if (hand[i]->sign==2 && hand[length-1]->sign==AS)
			{
					flush_length ++;
			}
		}
		else
		{
			flush_length=1;
			highest_id = i;
		}
		if(flush_length >= 5)
		{
			return highest_id;
		}
	}
	return -1;
}

/*
	returns the index of the highest card in a colored flush,
	returns -1 if not found
*/
int findColor(Card ** hand,int length){
	int counts[4];
	for (int i = 0 ; i < 4 ; i ++)
		counts[i]=0;
	for (int i = 0 ; i < length ; i ++)
		counts[hand[i]->color]++;

	for (int i = length-1 ; i >=0  ;i --){
		if(counts[hand[i]->color]>=5)
			return i;
	}
	return -1;
}

/* returns the highest  pair IN A FULL
	returns -1 if there is no Full
*/
int findFullPaire(Card ** hand,int length){

	int brelan_beginning = findBrelan(hand,length);
	if (brelan_beginning<0)
		return -1;

	int pairIndex = findPaire(hand+brelan_beginning+3,length - brelan_beginning-3);
	return (pairIndex<0)? findPaire(hand,brelan_beginning): pairIndex;
}

/* returns the highest brelan IN A FULL
	returns -1 if there is no Full
*/
int findFullBrelan(Card ** hand,int length){
	int brelan_beginning = findBrelan(hand,length);
	if (findFullPaire(hand,length)<0)
		return -1;
	return brelan_beginning;
}

/*
	returns the index of the highest card in a colored flush,
	returns -1 if not found
*/
int findColoredFlush(Card ** hand,int length){
	int colored_flush_length=1;
	Color current_color=hand[length-1]->color;
	int last_index=length-1;

	for (int i = length-2 ; i >=0  ;i --){
		if(hand[i]->sign+1==hand[i+1]->sign &&
			 hand[i]->color==current_color)
			colored_flush_length++;
		else if (hand[i]->sign==hand[i+1]->sign)
			continue;
		else{
			last_index=i;
			colored_flush_length=1;
		}
		if (colored_flush_length>=5)
			return last_index;
	}
	return -1;
}
