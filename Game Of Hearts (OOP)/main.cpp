// Pass #1
// I had to attend one of my family member's funeral out of state

/*
Author: Diwas Dulal
Description: This program is able to play the game of hearts where there are 4
players and each player deals a card from the deck and playes the games of heart
according the the rules for 13 rounds and it displays score of each player at
the end of each rounds then finally it tells who won the game at the end of the
13 rounds depending on who has the least amount of points
*/

#include "CardClass.h"
#include "PlayerClass.h"
#include "mytype.h"
#include <iomanip>
#include <iostream>
using namespace std;

const int MAX_ROUNDS = 13; // Maximum rounds
const int MAX_PLAYERS = 4; // Max Players
int round = 1;             // each round

// declare prototypes of the functions here
int FindLead(PlayerClass p[]);
void PlayRound(PlayerClass p[], CardStruct t[], int &lead);
void DisplayCard(const CardStruct c);
int GetChoice(PlayerClass user, suitType s, int turn);
int FindCollector(const CardStruct t[], int &score, suitType leadingSuit);
void DisplayScoreBoard(PlayerClass p[]);
int FindWinner(PlayerClass p[]);

int main() {

  // declare local variables
  CardClass deckOfCards;
  CardStruct
      table[MAX_PLAYERS]; // This structure holds the 4 cards played by // the 4
                          // players in one round of the game deck is created
  PlayerClass players[MAX_PLAYERS]; // user and players

  srand(time(NULL));

  // shuffle the deck of cards
  deckOfCards.ShuffleCard();

  // This for loop deals ONLY ONE card at a time
  // by repetitively calling the DealCard method of CardClass
  // Give Card to each player in a clockwise rotation format

  CardStruct card;
  while (!deckOfCards.IsEmpty()) {
    card = deckOfCards.DealCard();
    players[0].AddCard(card);
    card = deckOfCards.DealCard();
    players[1].AddCard(card);
    card = deckOfCards.DealCard();
    players[2].AddCard(card);
    card = deckOfCards.DealCard();
    players[3].AddCard(card);
  }
  // This for loop sorts each players cards
  for (int i = 0; i < MAX_PLAYERS; i++) {
    players[i].Sort();
  }
  // Find who leads the first round
  // int firstlead;
  int lead = FindLead(players);

  // displays layout the way it is in example
  cout << "**********************************************" << endl;
  cout << setw(26) << "HEARTS" << endl;
  cout << "**********************************************" << endl;

  // displayes who is the first lead
  if (lead != 0)
    cout << "Computer " << lead << " is the first lead" << endl;
  else {
    cout << "User is the first lead" << endl;
  }

  cout << endl;
  // loop iterates 13 rounds of the game
  while (round <= 13) {
    cout << "ROUND " << round << endl;
    cout << "Your Cards" << endl;
    players[0].DisplayCards();

    PlayRound(players, table, lead); // playround gets called everyround
    round++;                         // increment rounds
  }

  int winner;
  winner = FindWinner(players); // finds winner

  // displays winner
  if (winner == 0) {
    cout << "You Won!" << endl;
  } else {
    cout << "Player " << winner << " Won!" << endl;
  }
  // Find who is the winner

  // prints the player who won the game

  return 0;
}

// This function calls the PlayerClass member function to find who leads the
// first game
int FindLead(PlayerClass p[]) {
  int lead;
  for (int i = 0; i < MAX_PLAYERS; i++) {
    // checks who leads the game
    if (p[i].IsFirstLead()) {
      lead = i;
      break;
    }
  }
  return lead;
}

// This function plays one round of the game
// p[] pass in the 4 PlayerClass objects, i.e., the 4 players
// t[] will hold the 4 cards for a round
// lead will:
//    (1)pass in who should lead the current round, and
//    (2)pass back to the calling function who will lead the next round of the
//    game
void PlayRound(PlayerClass p[], CardStruct t[], int &lead) {
  int n = lead; // n is set to lead
  int choice;

  // goes through 4 times to be able to play each player's card
  for (int i = 0; i < MAX_PLAYERS; i++) {
    n = n %
        4; // n moded by 4 always brings it back to the right order when playing

    // if it is the first round and the first lead in the player it playes the 2
    // of clubs and displays the right player along with the card no matter if
    // it is user or computer
    if (p[n].GetCount() == 13 && p[n].IsFirstLead()) {
      t[n] = p[n].Play2Club();
      if (n == 0) {
        cout << endl;
        cout << "User is leading the round" << endl << endl;
        cout << "User "
             << ": ";
        DisplayCard(t[n]);

      } else {
        cout << endl;
        cout << "Computer " << n << " is leading the round" << endl << endl;
        cout << "Computer " << n << ": ";
        DisplayCard(t[n]);
      }
      // if lead is user and n is the turn is also user's than it displays the
      // right output and gets user's choice to be played
    } else if (lead == 0 && n == 0) {
      cout << endl;
      cout << "User is leading the round" << endl;
      cout << endl;
      choice = GetChoice(p[0], t[lead].Suit, lead); // gets user's choice
      t[n] = p[n].PlaySelectedCard(choice);         // plays user choice
      cout << "User "
           << ": ";
      DisplayCard(t[n]);
    }
    // if computer is the lead it plays the first card of their deck
    else if (n != 0 && n == lead) {
      cout << endl;
      cout << "Computer " << n << " is leading the round" << endl << endl;
      t[n] = p[n].StartOneHand(); // plays the first card in the computer's deck
      cout << "Computer " << n << ": ";
      DisplayCard(t[n]);
    } else {
      // if n is not leading it displays the leading suit of the round and lets
      // user pick a card that is valid and display it
      if (n == 0) {
        cout << endl << "Leading suit: ";
        if (t[lead].Suit == HEART) {
          cout << "Heart" << endl;
        } else if (t[lead].Suit == DIAMOND) {
          cout << "Diamond" << endl;
        } else if (t[lead].Suit == CLUB) {
          cout << "Club" << endl;
        } else {
          cout << "Spade" << endl;
        }
        choice = GetChoice(p[0], t[lead].Suit, lead);
        t[n] = p[n].PlaySelectedCard(choice);
        cout << "User: ";
        DisplayCard(t[n]);

      }
      // lets computer follow the card from the leading suit if it is in the
      // deck other wise play the first card and display it
      else {
        t[n] = p[n].FollowOneCard(t[lead].Suit);
        cout << "Computer " << n << ": ";
        DisplayCard(t[n]);
      }
    }
    n += 1; // adds 1 to n so it goes in the right order when being modded
  }

  // Finds who has the highest value of a round

  int score = 0;
  cout << endl;
  int collecter = FindCollector(t, score, t[lead].Suit);
  // And assigns lead to who has the highest value
  lead = collecter;
  // Display which player gets how many points on this round
  if (collecter == 0) {
    cout << "User gets " << score << " points." << endl;
  } else {
    cout << "Computer " << collecter << " get " << score << " points." << endl;
  }
  cout << endl;

  // Adds current round's score to the player who had the highest value
  p[collecter].AddScore(score);
  // Prints the score board

  DisplayScoreBoard(p);
  cout << endl;
}

// This function prints one card's suit and value
void DisplayCard(const CardStruct c) {
  string value = to_string(c.Value);
  switch (c.Value) {
  case 14:
    value = "Ace";
    break;
  case 13:
    value = "King";
    break;
  case 12:
    value = "Queen";
    break;
  case 11:
    value = "Jack";
    break;
  }
  if (c.Suit == HEART) {
    cout << value << " of "
         << "Hearts" << endl;
  } else if (c.Suit == SPADE) {
    cout << value << " of "
         << "Spade" << endl;
  } else if (c.Suit == CLUB) {
    cout << value << " of "
         << "Club" << endl;
  } else if (c.Suit == DIAMOND) {
    cout << value << " of "
         << "Diamond" << endl;
  }
}

// This function read the user's choice
// turn : if it is 0, the user is leading the round; otherwise the user is
// following in the round s : leading suit of the current game
int GetChoice(PlayerClass user, suitType s, int turn) {
  // declare local variables
  int choice;
  // if the user is leading the round get a choice from the user
  if (turn == 0) {
    cout << " Please enter the card number you want to play:  ";
    cin >> choice;
    return choice;
  }

  // if the user is playing after the lead,
  // then get a choice and check if it is a valid choice
  // continue to ask until a valid choice is made

  else if (turn != 0) {
    bool valid = false;
    // while loop goes through until valid variable is true
    while (valid != true) {
      cout << " Please enter the card number you want to play:  ";
      cin >> choice;
      valid = user.IsValidChoice(s, choice);
      if (valid == false) {
        cout << "Not a valid choice." << endl;
      }
    }
  }
  return choice; // if it is valid, it returns the choice
}
// This function find who has played the card of highest value of the round
// score is total points
int FindCollector(const CardStruct t[], int &score, suitType leadingSuit) {
  // declare local variables
  int highest = 0;
  int collector = 0;
  int total = 0;
  // loop to sum up all of the points
  // and then find who has played the card of highest value for the round

  // the array index corresponding to the player with the highest value for
  // the round is retured.
  for (int i = 0; i < MAX_PLAYERS; i++) {
    if (t[i].Suit == leadingSuit) {
      if (t[i].Value > highest) {
        highest = t[i].Value;
        collector = i;
      }
    }
    total += t[i].Points; // adds points of all players
  }
  score = total;
  return collector;
}

// This function prints each player's score
void DisplayScoreBoard(PlayerClass p[]) {
  cout << "-----Score Board-----" << endl;
  cout << "User: " << p[0].GetScore() << endl;
  for (int i = 1; i < MAX_PLAYERS; i++) {
    cout << "Computer " << i << ": " << p[i].GetScore() << " points" << endl;
  }
}

// This function finds who won the game
// winner's index is retured
int FindWinner(PlayerClass p[]) {
  int num = p[0].GetScore();
  int index = 0;
  // gets though all players and getst the index or the player with the least
  // points
  for (int i = 1; i < MAX_PLAYERS; i++) {
    if (p[i].GetScore() < num) {
      num = p[i].GetScore();
      index = i;
    }
  }
  return index;
}