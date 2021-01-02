#include "best.h"
#define min(A,B) ((A)>(B))?(B):(A)

Card** concatCards(Card ** cards1, int size1,Card ** cards2, int size2){
	int concat_size = size1+size2;
	Card** cards_concat = malloc(concat_size*sizeof(Card*));
	if(cards_concat==NULL){
		perror("malloc");
		exit(1);
	}
	for(int i=0;i<size1;i++){
		cards_concat[i]=cards1[i];
	}
	for(int i=0;i<size2;i++){
		cards_concat[i+size1]=cards2[i];
	}
	return cards_concat;
}

/**
	returns 1 if the hand1 is better, -1 if it is not and 0 if it is a draw
**/
/*int getScore(Card ** hand1,int size){
	CardSet * cs1 = makeCardSet(hand1,size);
	destroyCardSet(cs1);

	return score;
}*/
int compareRemainig(CardSet  * cs1,CardSet  * cs2,int max){
	int stop = min(cs1->total_size-cs1->set_size-1,max);
	for(int i=0;i<stop;i++)
		if(cs1->remaining[i]->sign != cs2->remaining[i]->sign)
			return cs1->remaining[i]->sign - cs2->remaining[i]->sign;
	return 0;
}

int compareSimple(CardSet  * cs1,CardSet  * cs2){
	for(int i=0;i<cs1->set_size;i++)
		if(cs1->set[i]->sign != cs2->set[i]->sign)
			return cs1->set[i]->sign - cs2->set[i]->sign;
	return compareRemainig(cs1,cs2,4);
}

int comparePair(CardSet  * cs1,CardSet  * cs2){
	for(int i=0;i<cs1->set_size;i++)
		if(cs1->set[i]->sign != cs2->set[i]->sign)
			return cs1->set[i]->sign - cs2->set[i]->sign;
	return compareRemainig(cs1,cs2,4);
}

int compareDouble(CardSet  * cs1,CardSet  * cs2){
	for(int i=0;i<cs1->set_size;i++){
		if(cs1->set[i]->sign != cs2->set[i]->sign){
			return cs1->set[i]->sign - cs2->set[i]->sign;
		}
	}
	return compareRemainig(cs1,cs2,cs1->total_size-cs1->set_size);
}

int compareBrelan(CardSet  * cs1,CardSet  * cs2){
	for(int i=0;i<cs1->set_size;i++)
		if(cs1->set[i]->sign != cs2->set[i]->sign)
			return cs1->set[i]->sign - cs2->set[i]->sign;
	return compareRemainig(cs1,cs2,2);
}

int compareFlush(CardSet  * cs1,CardSet  * cs2){
	if(cs1->set[0] != cs2->set[0])
		return cs1->set[0] != cs2->set[0];
	return 0;
}

int compareColor(CardSet  * cs1,CardSet  * cs2){
	for(int i=0;i<cs1->set_size;i++)
		if(cs1->set[i]->sign != cs2->set[i]->sign)
			return cs1->set[i]->sign - cs2->set[i]->sign;
	return 0;
}

int compareFull(CardSet  * cs1,CardSet  * cs2){
	for(int i=0;i<cs1->set_size;i++){
		if(cs1->set[i]->sign != cs2->set[i]->sign)
			return cs1->set[i]->sign - cs2->set[i]->sign;
	}
	return 0;
}

int compareSquare(CardSet  * cs1,CardSet  * cs2){
	if(cs1->set[0] != cs2->set[0])
		return cs1->set[0] - cs2->set[0];
	return compareRemainig(cs1,cs2,1);
}

int compareColored(CardSet  * cs1,CardSet  * cs2){
	return compareFlush(cs1,cs2);
}

int compareSameType(CardSet * cs1,CardSet * cs2){
	if(cs1->type==SINGLE){
		return compareSimple(cs1,cs2);
	}
	if(cs1->type==PAIR){
		return comparePair(cs1,cs2);
	}
	if(cs1->type==DOUBLE){
		return compareDouble(cs1,cs2);
	}
	if(cs1->type==BRELAN){
		return compareBrelan(cs1,cs2);
	}
	if(cs1->type==FLUSH){
		return compareFlush(cs1,cs2);
	}
	if(cs1->type==COLOR){
		return compareColor(cs1,cs2);
	}
	if(cs1->type==SQUARE){
		return compareSquare(cs1,cs2);
	}
	if(cs1->type==COLORED){
		return compareColored(cs1,cs2);
	}
	if(cs1->type==FULL){
		return compareFull(cs1,cs2);
	}
	else{
		fprintf(stderr, "ERROR type undefined\n" );
		exit(1);
	}
}

int isBetter(Card ** hand1,Card ** hand2,int size){
	CardSet * cs1 = initCardSet(hand1,size);
	CardSet * cs2 = initCardSet(hand2,size);

	if(cs1->type != cs2->type ){
		int result = cs1->type - cs2->type;
		destroyCardSet(cs1);
		destroyCardSet(cs2);
		return result;
	}

	int result =  compareSameType(cs1,cs2);

	destroyCardSet(cs1);
	destroyCardSet(cs2);
	return result;
}
