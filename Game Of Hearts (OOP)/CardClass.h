// header file for the CardClass
#ifndef _CARDCLASS_H_
#define _CARDCLASS_H_

#include <iostream>
using namespace std;
#include "mytype.h"
#include <vector>

class CardClass {

public:
  //Default Constructor
  CardClass();
  //Shuffles the card of the deck
  void ShuffleCard();
  //deals last card from the deck
  CardStruct DealCard();
  //gets the size of the deck currently
  int GetSize();
  //checks of deck is empty
  bool IsEmpty();

private:
  static const int DECK_SIZE = 52;
  CardStruct Deck[DECK_SIZE]; // card of struct CardStruct of size 52
  int Size = 0;  //size of the deck
};

#endif
