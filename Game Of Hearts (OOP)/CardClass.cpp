// implementation file for CardClass
#include "CardClass.h"
#include "mytype.h"
#include <iostream>
using namespace std;

CardClass::CardClass() {
  //goes though the deck and adds each card with correct info to the deck
  suitType j;
  CardStruct temp;
  for (j = HEART; j <= SPADE; j = static_cast<suitType>(j + 1)) {
    for (int k = 2; k <= 14; k++) {
      temp.Suit = j;
      temp.Value = k;
      if (j == HEART && k < 10) {
        temp.Points = 5;
      } else if (j == HEART && k >= 10) {
        temp.Points = 10;
      } else if (j == SPADE && k == 12) {
        temp.Points = 100;
      } else if (j == CLUB && k == 11) {
        temp.Points = -100;
      } else {
        temp.Points = 0;
      }
      Deck[Size] = temp;
      Size++;//increments size by 1
    }
  }
}

//gets a random index and replaces it with i in each index
void CardClass::ShuffleCard() {
  CardStruct tempCard;
  for (int i = 0; i < 52; i++) {
    int rand2 = rand() % 52;
    if (i != rand2) {
      tempCard = Deck[i];
      Deck[i] = Deck[rand2];
      Deck[rand2] = tempCard;
    }
  }
}

//returns the last card from the deck
CardStruct CardClass::DealCard() {
  CardStruct temp;
  temp = Deck[Size - 1];
  Size -= 1; //dectements size by 1
  return temp;
}
//returns the size of the deck
int CardClass::GetSize() { return Size; };

//returns true if deck is empty or size is 0
bool CardClass::IsEmpty() {
  if (Size == 0) {
    return true;
  }
  return false;
}
