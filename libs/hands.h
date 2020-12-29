#ifndef _hands___
#include  "card.h"
#define _hands___


typedef enum setType{
  SINGLE,
  PAIR,
  DOUBLE,
  BRELAN,
  FLUSH,
  COLOR,
  FULL,
  SQUARE,
  COLORED,
  UNDEFINED
} SetType;

typedef struct cardSet{
  Card ** set;
  Card ** remaining;//les cartes restantes du represente
  SetType type;
  int set_size;
  int total_size;
}CardSet;

CardSet * makeCardSet(Card ** hand,int length);
CardSet * initCardSet(Card ** hand,int length);
void destroyCardSet(CardSet *cs);
void addCardToSet(CardSet * cs, Card * c);

#endif
/*
RULES
  [Ah Kh Qh Jh Th] 	Royal Flush
    Das most powerful, but also the rarest poker hand: the highest possible straight from ace down to ten in the same color (suited).
  [8s 7s 6s 5s 4s] 	Straight Flush
    A suited straight.
  [8h 8s 8d 8c] 	Four of a Kind
    Also called Poker or Quads. Four cards of the same value. If two players both hold Quads, the player with the highest fifth card wins. If this card is the same for both players (e.g. because an ace is on the flop), the pot is split between the two players.
  [Qd Qs Qc 9h 9d] 	Full House
    Three of a kind and a pair. If more than one player has a Full House, the one with the highest three of a kind wins the pot. If two players have the same three of a kind cards, the player with the highest pair wins. If all five cards are identical, the pot will be spilt.
  [As Js 9s 6s 4s] 	Flush
    Five cards of the same color, e.g. five diamonds. If two players have a Flush, the player with the highest card wins the pot.
  [Qs Jh Th 9c 8d] 	Straight
    Five cards in a row. An ace can either be the highest or the lowest card of the straight, but “around-the-corner” straights do not exist in Texas Hold’em.
  [Th Ts Td] 	Three of a Kind
    Also called a Set or Trips. Three cards of the same value. If two players have the same Trips, the player with the highest additional card wins.
  [Kh Ks 8s 8d] 	Two Pairs
    Two times two cards of the same value. The player with the highest pair wins if there is more than one player holding two pair.
  [Qd Qc] 	Pair
    Two cards of the same value. If more the one player has a pair, the one with the highest pair wins. If this has the same value, the player with the highest addional card wins.
  [Ac] 	High Card
    If no player has a pair or better, the one with the highest card wins. The ranking is Ace, Kind, Queen, Jack, Ten, Nine, Eight and so forth. If the two players have the same highest card, the one with the next highest out of his five best cards wins. The color of the cards doesn’t matter in Texas Hold’em.
*/
