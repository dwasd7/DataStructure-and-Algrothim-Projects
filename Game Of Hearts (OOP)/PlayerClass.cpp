#include "PlayerClass.h"
#include "CardClass.h"
#include "mytype.h"
#include <cctype>
#include <iomanip>
#include <iostream>
//#include <vector>


//Default Constructor
PlayerClass::PlayerClass() {
  count = 0; //count of cards in a player's hand
  score = 0; //player's score
}

// Adds one card to the player's hand.
// Cards are always added to one’s hand by adding it at the end of all cards
// already in one’s hand. pre-condition: player has less than 13 cards
// post-condition: player has one more card in the hand count is increased by
// 1
void PlayerClass::AddCard(CardStruct card) {
  hand[count] = card;//adds card to the count index which first starts from 0
  count += 1;
  return;
}

// prints out the current cards the player has
// pre-condition:  The player has some cards on hand
// post-condition: the player’s cards are displayed.
void PlayerClass::DisplayCards() const {
  if (count >= 1) {
    cout << left << setw(10) << "#" << setw(10) << "SUIT" << setw(10) << "VALUE"
         << setw(10) << "POINTS" << endl;
    for (int i = 0; i < count; i++) {
      string value = to_string(hand[i].Value);

      switch (hand[i].Value) {
      case 14:
        value = "A";
        break;
      case 13:
        value = "K";
        break;
      case 12:
        value = "Q";
        break;
      case 11:
        value = "J";
        break;
      }

      if (hand[i].Suit == HEART) {
        cout << left << setw(10) << i + 1 << setw(10) << "Heart" << setw(10)
             << value << setw(10) << hand[i].Points << endl;
      } else if (hand[i].Suit == SPADE) {
        cout << left << setw(10) << i + 1 << setw(10) << "Spade" << setw(10)
             << value << setw(10) << hand[i].Points << endl;
      } else if (hand[i].Suit == CLUB) {
        cout << left << setw(10) << i + 1 << setw(10) << "Club" << setw(10)
             << value << setw(10) << hand[i].Points << endl;
      } else if (hand[i].Suit == DIAMOND) {
        cout << left << setw(10) << i + 1 << setw(10) << "Diamond" << setw(10)
             << value << setw(10) << hand[i].Points << endl;
      }
    }
  }
}

// select to play the first card that has the suit supplied from the client
// program if no card can be found that has the suit supplied by the client
// program, the first card from the hand is played pre-condition: there are >=
// 1 cards in hand post-condition: a card is returned, count is decremented by
// 1
CardStruct PlayerClass::FollowOneCard(suitType s) {
  CardStruct temp;
  // goes through the dec and gets the first card with the suit and returns it
  for (int i = 0; i < count; i++) {
    if (hand[i].Suit == s) {
      temp = hand[i];
      RemoveCard(i);
      count--;
      break;
    } else {
      temp = hand[0];
    }
  }
  if (temp.Suit == hand[0].Suit && temp.Value == hand[0].Value) {
    RemoveCard(0);
    count--;
  }
  return temp;
  // right card is played
}

// Removes the card out of the index and pushes every card left and deletes the
// memory for the last space
void PlayerClass::RemoveCard(int index) {
  if (count >= 1) {
    for (int i = index; i < count; i++) {
      hand[i] = hand[i + 1];
    }
  }
}

// plays the first card of a round. The top card in the deck is selected
// pre-condition: there are >= 1 card in the hand
// post-condition: one card is played/returned, count is decremented by 1
CardStruct PlayerClass::StartOneHand() {
  CardStruct temp = hand[0];
  RemoveCard(0);
  count--;
  return temp;
}

// Checks to see if the player should lead the
// first round in the game, e.g., check whether the player has 2 of club
// pre-condition: the hand is full (have 13 cards)
// post-condition: if this player has 2 of club, true is returned, otherwise,
// return false.
bool PlayerClass::IsFirstLead() const {

  // loop through until 2 of club is found or return false
  for (int i = 0; i < count; i++) {
    if (hand[i].Suit == CLUB && hand[i].Value == 2) {
      return true;
    }
  }
  return false;
}

// play card 2 of club
// pre-condition: the player has 2 of club on hand
// post-condition: 2 of club is played/returned. Cards following “2 of Club”
// is shifted up
//                          number of cards remaining on hand is decremented
//                          by 1
CardStruct PlayerClass::Play2Club() {
  for (int i = 0; i < 13; i++) {
    if (hand[i].Suit == CLUB && hand[i].Value == 2) {
      CardStruct temp = hand[i];
      RemoveCard(i);
      count--;
      return temp;
    }
  }
  return hand[0];
}

// The current score of the player is returned
int PlayerClass::GetScore() const { return score; }

// the points from the current round is added to the current player's score
// pre-condition: a point value is sent in from client
// post-condition: the player's score is increased by the points from the
// client program
void PlayerClass::AddScore(int point) { score += point; }

// Return the number of cards the player has
// pre-condition: none
// post-condition:   the number of cards currently in the player’s hand is
// returned
int PlayerClass::GetCount() const { return count; }

// sorts the cards by suit
// pre-condition: there are >=1 cards in hand
// post-condition: the cards are sorted by suit
void PlayerClass::Sort() {
  if (count <= 1) {
    return;
  }
  int i = 0;
  //goes though nested loop and sorts each card by swapping 
  for (int i = 1; i < count; i++) {
    int j = i - 1;
    while (j >= 0 && hand[j + 1].Suit < hand[j].Suit) {

      CardStruct temp = hand[j];
      hand[j] = hand[j + 1];
      hand[j + 1] = temp;
      j--;
    }
  }
  return;
}

// plays the card selected by user
// pre-condition:  the card number selected by the user is supplied
// post-condition: the card corresponding to the user choice is
// played/returned the number
//                          of cards in player's hand is decremented by 1. If
//                          this card is in the
//                         middle of one’s hand, all cards following that card
//                         are shifted as a result of removing the card
CardStruct PlayerClass::PlaySelectedCard(int choice) {
  CardStruct temp = hand[choice - 1];
  //goes though to play the right card
  for (int i = 0; i < count; i++) {
    if (i + 1 == choice) {
      RemoveCard(i);
      count--;
      return temp;
    }
  }
  return temp;
}

// Checks to see if the card the user chooses is a valid choice, e.g., whether
// it matches the leading suit on that hand, if he has any. pre-condition: the
// player's choice and the leading suit are supplied post-condition: returns
// true if
//         (1) user has cards of leading suit and the choice card is of that
//         suit, or (2) user does not have card of leading suit
//      and returns false otherwise
bool PlayerClass::IsValidChoice(suitType suit, int choice) const {
  int n = 0; // checks how many cards of the leading suit there is and if it is 0 than the choice is still valid
  //goes through a loop to check if the suit matches and the choice-1 matches with the index
  for (int i = 0; i < count; i++) {
    if (hand[i].Suit == suit) {
      n += 1;
    }
    if (hand[i].Suit == suit && i == choice - 1) {
      return true;
    }
  }
  //if no card of the suit found than it is valid so it returns true
  if (n == 0) {
    return true;
  }
  return false;//or returns false
}