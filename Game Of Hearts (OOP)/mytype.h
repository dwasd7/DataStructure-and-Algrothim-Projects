// define the enum type for card suits here
// also define the card struct type here
#ifndef _CARDTYPE_H_
#define _CARDTYPE_H_

#include <iostream>
using namespace std;

//enumurator type suitType of Suits
enum suitType{HEART,CLUB,DIAMOND,SPADE};


//Struct of a Card that holds Suit, Value, and Points of each card
struct CardStruct{
  suitType Suit;
  int Value;
  int Points;
};

#endif