#include "hands.h"
#include "game.h"

void swap(Card ** cards,int ind1, int ind2){
	Card * tmp = cards[ind2];
	cards[ind2] = cards[ind1];
	cards[ind1] = tmp;
}

void removeFromRemaining(CardSet * cs, Card * c){
	for(int i = 0 ; i < cs->total_size-cs->set_size-1;i++){
		if(cs->remaining[i]==c){
			swap(cs->remaining,i,cs->total_size-cs->set_size-1);
			return;
		}
	}
}

void addToSet(CardSet * cs, Card * c){
	cs->set[cs->set_size++]=c;
}


void addCardToSet(CardSet * cs, Card * c){
	removeFromRemaining(cs, c);
	addToSet(cs, c);
}

//==============================================================================

void fillSimple(CardSet* cs,Card ** hand,int length){
	addCardToSet(cs,hand[length-1]);
	cs->type=SINGLE;
}

void fillPair(CardSet* cs,Card ** hand,int length){
	for (int i = length-2 ; i >=0  ;i --){
		if (hand[i]->sign == hand[i+1]->sign){
			addCardToSet(cs,hand[i+1]);
			addCardToSet(cs,hand[i]);
			cs->type=PAIR;
			return;
		}
	}
}

void fillBrelan(CardSet*cs ,Card ** hand,int length){
	for (int i = length-3 ; i >=0  ;i --){
		if (hand[i]->sign == hand[i+1]->sign && hand[i+1]->sign == hand[i+2]->sign){
			addCardToSet(cs,hand[i+2]);
			addCardToSet(cs,hand[i+1]);
			addCardToSet(cs,hand[i]);
			cs->type=BRELAN;
			return;
		}
	}
}

void fillDoublePair(CardSet*cs ,Card ** hand,int length){
	int counter[13];//compteur des cartes, 0 et 1 sont absents, donc
	for(int i=0;i<14;i++)
		counter[i]=0;
	for(int i=0;i<length;i++)
		counter[hand[i]->sign-2]++;
	int biggest_pair = -1;
	int secd_biggest = -1;

	for(int i=0;i<14;i++)
		if(counter[i]>=2)
			biggest_pair=i+2;
	for(int i=0;i<14;i++)
		if(counter[i]>=2 && i+2 != biggest_pair)
			secd_biggest=i+2;

	if(biggest_pair<0 || secd_biggest<0)
		return;

	for(int i=0;i<length;i++)
		if(hand[i]->sign==biggest_pair){
			addCardToSet(cs,hand[i]);
		}
	for(int i=0;i<length;i++)
		if(hand[i]->sign==(Sign)secd_biggest){
			addCardToSet(cs,hand[i]);
		}
	cs->type=DOUBLE;
}

void fillFlush(CardSet*cs ,Card ** hand,int length){
	int indexes[5];
	int flush_length=1;
	indexes[0] = 	length - 1;

	for (int i = length-2 ; i >=0  ;i --)
	{
		if (hand[i]->sign == hand[i+1]->sign)
			continue;
		if (hand[i]->sign+1 == hand[i+1]->sign){
			indexes[flush_length++]=i;
		}
		else{
			flush_length=1;
			indexes[0] = i;
		}
		if(flush_length >= 5){
			cs->type=FLUSH;
			for(int j=0;j<5;j++)
				addCardToSet(cs,hand[indexes[j]]);
			return;
		}
	}
	if(hand[0]->sign==2 && hand[length-1]->sign==AS && flush_length==4){
		indexes[4]=length-1;
		cs->type=FLUSH;
		for(int j=0;j<5;j++)
			addCardToSet(cs,hand[indexes[j]]);
	}
}

void fillColor(CardSet*cs, Card ** hand,int length){
	int trefles[5];
	int coeurs[5];
	int carreaux[5];
	int piques[5];

	int n_trefles, n_coeurs, n_carreaux,n_piques;
	n_trefles=n_coeurs=n_carreaux=n_piques=0;

	for (int i = length-1 ; i >=0  ;i --){
		if(hand[i]->color==TREFLE)
			trefles[n_trefles++]=i;
		if(hand[i]->color==COEUR)
			coeurs[n_coeurs++]=i;
		if(hand[i]->color==PIQUE)
			piques[n_piques++]=i;
		if(hand[i]->color==CARREAU)
			carreaux[n_carreaux++]=i;
	}
	if(n_coeurs<5 && n_carreaux<5 && n_trefles<5 && n_piques<5)
		return;
	cs->type=COLOR;
	if(n_coeurs>=5)
		for(int i=0;i<5;i++){
			addCardToSet(cs,hand[coeurs[i]]);
		}
	if(n_piques>=5)
		for(int i=0;i<5;i++){
			addCardToSet(cs,hand[piques[i]]);
		}
	if(n_trefles>=5)
		for(int i=0;i<5;i++){
			addCardToSet(cs,hand[trefles[i]]);
		}
	if(n_carreaux>=5)
		for(int i=0;i<5;i++){
			addCardToSet(cs,hand[carreaux[i]]);
		}
}

void fillFull(CardSet*cs, Card ** hand,int length){
	int counter[13];//compteur des cartes, 0 et 1 sont absents, donc
	for(int i=0;i<13;i++)
		counter[i]=0;
	for(int i=0;i<length;i++)
		counter[hand[i]->sign-2]++;

	int biggest_pair = -1;
	int biggest_brelan = -1;
	for(int i=0;i<13;i++)
		if(counter[i]>=3){
			biggest_brelan=i+2;
		}
	for(int i=0;i<13;i++)
		if(counter[i]>=2 && i+2 != biggest_brelan){
			biggest_pair=i+2;
		}
	if(biggest_pair>=0 && biggest_brelan>=0){
		for(int i=length-1;i>=0 && cs->set_size<3;i--){
			if(hand[i]->sign==biggest_brelan)
				addCardToSet(cs,hand[i]);
		}
		for(int i=length-1;i>=0 && cs->set_size<5;i--){
			if(hand[i]->sign==biggest_pair)
				addCardToSet(cs,hand[i]);
		}
		cs->type=FULL;
		return;
	}
}

void fillSquare(CardSet*cs, Card ** hand,int length){
	for (int i = length-4 ; i >=0  ;i --){
		if (hand[i]->sign == hand[i+1]->sign && hand[i+1]->sign == hand[i+2]->sign&& hand[i+2]->sign == hand[i+3]->sign){
			cs->type=SQUARE;
			addCardToSet(cs,hand[i+3]);
			addCardToSet(cs,hand[i+2]);
			addCardToSet(cs,hand[i+1]);
			addCardToSet(cs,hand[i]);
			return;
		}
	}
}

void fillColoredFlush(CardSet*cs,Card ** hand,int length){
	int indexes[5];
	int flush_length=1;
	indexes[0] = 	length - 1;
	Color flush_color = hand[indexes[0]]->color;
	for (int i = length-2 ; i >=0  ;i --)
	{
		if(flush_color==hand[i]->color
				&& hand[i]->sign+1 == hand[i+1]->sign){
			indexes[flush_length++]=i;
		}
		else if (hand[i]->sign == hand[i+1]->sign){
			continue;
		}
		else{
			indexes[flush_length=0]=i;
		}
		if(flush_length>=5){

			for(int i=0;i<5;i++){
					addCardToSet(cs,hand[indexes[i]]);
			}
			cs->type=COLORED;
			return;
		}
	}
	if(flush_length==4 && hand[indexes[3]]->sign==2){
		for(int i=length-1;i>=0 && hand[i]->sign==AS;i--)
			if(hand[i]->color==flush_color){
				indexes[flush_length++]=i;
				break;
			}
	}
	if(flush_length>=5){
		for(int i=0;i<5;i++){
				addCardToSet(cs,hand[indexes[i]]);
		}
		cs->type=COLORED;
	}
}

//==============================================================================
//Remplis un cardset en fonction des cartes données en entrée
void fillSet(CardSet*cs,Card **cards,int length){
	void (*fillers[8])(CardSet*cs,Card ** hand,int length) = {
		&fillColoredFlush,
		&fillSquare,
		&fillFull,
		&fillColor,
		&fillFlush,
		&fillBrelan,
		&fillDoublePair,
		&fillPair
	};
	for(int i=0;i<8;i++){
		fillers[i](cs,cards,length);
		if(cs->type != UNDEFINED){
			return;
		}
	}
	fillSimple(cs,cards,length);
}


CardSet * makeCardSet(Card ** hand,int length){
	CardSet * cs = malloc(sizeof(CardSet));
	if(cs==NULL){
		perror("malloc");
		exit(1);
	}
	cs->set=malloc(sizeof(Card*)*length);
	cs->remaining=malloc(sizeof(Card*)*length);
	if(cs->set==NULL||cs->remaining==NULL){
		perror("malloc");
		exit(1);
	}

	for(int i=0;i<length;i++){
		cs->remaining[i]=hand[i];
	}
	cs->set_size=0;
	cs->total_size=length;
	cs->type=UNDEFINED;
	return cs;
}

/** create a cardset**/
CardSet * initCardSet(Card ** hand,int length){
	sortHand(hand, length);
	CardSet* cs = makeCardSet(hand,length);

	fillSet(cs,hand,length);
	return cs;
}

/** create a cardset**/
void destroyCardSet(CardSet *cs){
	free(cs->remaining);
	free(cs->set);
	free(cs);
}
