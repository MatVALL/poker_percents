#include <stdio.h>
#include <sys/time.h>
#include "game.h"
#include "best.h"

//TODO make the srand depend of the pid
void initRand(){
	struct timeval time;
	gettimeofday(&time,NULL);
	srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//memory leak : free cardToText
void printGame(Game * g){
	printf("hand:\n");
	printCard(*g->hand[0]);printCard(*g->hand[1]);
	printf("\n");
	for(int i=0;i<g->n_drawn;i++){
		printCard(*(g->drawn[i]));
	}
}

/**
	return true if the card given is in the hand or has been drawn
	return false otherwise
**/
int cardIsInGame(Card * c, Game * g){
	for(int i=0;i<g->n_drawn;i++){
		if(g->drawn[i]->sign==c->sign && g->drawn[i]->color==c->color)
			return 1;
	}
	if(g->n_drawn>0&&  g->drawn[0]->sign==c->sign && g->drawn[0]->color==c->color)
		return 1;
	if(g->n_drawn>1&& g->drawn[1]->sign==c->sign && g->drawn[1]->color==c->color)
		return 1;
	return 0;
}

//TODO : simulate sorted ?? (hand et game, pour test)
int simulateNextHand(Card ** cards_simulated,int n_cards,int *first){
	if(*first){
		*first=0;
		for(int i=0;i<n_cards;i++)
			cards_simulated[i]=makeCard(0,2);
		return 1;
	}
	for(int i=0;i<n_cards;i++){
		if(cards_simulated[i]->sign==AS && cards_simulated[i]->color == 3){//temps de faire la retenue
			cards_simulated[i]->sign=2;
			cards_simulated[i]->color=0;
			continue;
		}
		if(cards_simulated[i]->sign==AS){
			cards_simulated[i]->color++;
			cards_simulated[i]->sign=1;
		}
		cards_simulated[i]->sign++;
		return 1;
	}
	return 0;
}

void simulateRandom(Card ** cards_simulated,int n_cards){
	for(int i=0;i<n_cards;i++){
		cards_simulated[i]->sign  = (rand() % 13) + 2;
		cards_simulated[i]->color = rand() %  4 ;
	}
}

int isCorrect(Game * g, Card ** simulated_cards,int n_simulated){
	for (int i=0;i<n_simulated;i++)
		if(cardIsInGame(simulated_cards[i],g))
			return 0;
	return 1;
}

//utile pour quand il y a plusieurs cartes tirées,
//pour ce qui est de savoir si une carte est
double getProba(Game * g){
	int n_played = 0;
	int n_won = 0;

	//on simule toutes les cartes du joueur adverse et toutes les cartes à venir
	int n_simulated = 2+5-g->n_drawn;
	Card ** simulated_cards = malloc(sizeof(Card*)*n_simulated);
	int first=1;
	while(simulateNextHand(simulated_cards,n_simulated,&first)){
		//si une carte est présente en double dans le jeu après simulation
		if(!isCorrect(g,simulated_cards,n_simulated))
				continue;

		//pour eviter malloc et free, faire le malloc ç l'exterieur ?
		Card ** all_drawn = concatCards(simulated_cards+2,n_simulated-2,g->drawn,g->n_drawn);
		Card ** player_hand = concatCards(all_drawn,5,g->hand,2);
		Card ** opponent_hand = concatCards(all_drawn,5,simulated_cards,2);

		sortHand(player_hand,7);
		sortHand(opponent_hand,7);

		if(isBetter(player_hand,opponent_hand,7)>0){
			n_won++;
		}
		n_played++;
		free(all_drawn);
		free(player_hand);
		free(opponent_hand);
	}
	free(simulated_cards);
	return (double)n_won/n_played;
}

double getProbaMonteCarlo(Game * g,int n){
	int n_played = 0;
	int n_won = 0;
	//on simule toutes les cartes du joueur adverse et toutes les cartes à venir
	int n_simulated = 2+5-g->n_drawn;
	Card ** simulated_cards = malloc(sizeof(Card*)*n_simulated);
	for(int i=0;i<n_simulated;i++)
		simulated_cards[i]=makeCard(0,2);
	for(int i=0;i<n;i++){
		simulateRandom(simulated_cards,n_simulated);
		//si une carte est présente en double dans le jeu après simulation
		if(!isCorrect(g,simulated_cards,n_simulated)){
			i--;
			continue;
		}
		//pour eviter malloc et free, faire le malloc ç l'exterieur ?
		Card ** all_drawn;
		if(n_simulated>2)
			all_drawn = concatCards(simulated_cards+2,n_simulated-2,g->drawn,g->n_drawn);
		else{
			all_drawn = g->drawn;
		}
		Card ** player_hand = concatCards(all_drawn,5,g->hand,2);
		Card ** opponent_hand = concatCards(all_drawn,5,simulated_cards,2);

		sortHand(player_hand,7);
		sortHand(opponent_hand,7);

		if(isBetter(player_hand,opponent_hand,7)>0){
			n_won++;
		}
		n_played++;
		if(n_simulated>2)
			free(all_drawn);
		free(player_hand);
		free(opponent_hand);
	}
	free(simulated_cards);
	return (double)n_won/n_played;
}

int main(int argc, char**argv){
	srand(time(NULL));
	if(argc<2){
		fprintf(stderr, "Usage : ./poker_play game_file\n");
		exit(0);
	}
	printf("creating game\n");
	Game * g = makeGame(argv[1]);

	printf("calculating ...\n");
	printf("proba MC : %lf\n",getProbaMonteCarlo(g,1000000));
	printf("proba : %lf\n",getProba(g));
	
	destroyGame(g);
	return 0;
}
