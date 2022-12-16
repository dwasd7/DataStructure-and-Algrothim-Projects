
// Name :Diwas Dulal
// Description: This program creates a Binary Search Tree Class where each word
// and its information is stored in the data section of each node. This is done
// by reading a data file and seperating each words that conde in a consecutive
// sequence of letters of alphabet amd checks if the word is already in the tree
// and if it is, updates the inforamtion of the word
// (count,linenumber,lastline), otherwise, it creates a temp struct of wordEntry
// defind in the other file and add that word along with its inforamtion to the
// temp then calls a fucntion inside the bst to insert the temp structure in the
// right place. Then at the end the program displays it using a inorder
// traversal of the bst.

#include "BST.h"
#include "wordEntry.h"
#include <algorithm> //used in multiple cases to make code simpler
#include <cassert>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream> //used to split the words from a line
#include <string>

using namespace std;
int isNotAlphaNum(char c);

int main() {
  bstClass bst; // bst object
  string file;
  cout << "This program will read a file and create a list of word frequency "
          "and line numbers."
       << endl
       << endl;
  cout << "Please enter the name of the file to read:  ";
  cin >> file;
  cout << endl << endl;
  // open the file into myIn
  ifstream myIn(file);
  assert(myIn);

  // variables
  string line, word;
  int count = 1;   // used to add to the count of a word
  int linenum = 1; // used to store each line number

  while (getline(myIn, line)) {
    // replaces all non alpabetic characters with  " " so word can be defined as
    // a consecutive sequence of letters of alphabet
    replace_if(line.begin(), line.end(), isNotAlphaNum, ' ');
    stringstream s(line);
    while (s >> word) {
      // Remove a none Alphabetic characters from the word
      for (int i = 0; i < word.size(); i++) {
        if (word[i] < 'A' || word[i] > 'Z' && word[i] < 'a' || word[i] > 'z') {
          word.erase(i, 1);
          i--;
        }
      }
      // change eachletter to lowercase
      for (auto &x : word) {
        x = tolower(x);
      }
      // checks if the word is already in the bst and if true, then updates that
      // node
      if (bst.check(word) == true) {
        bst.update(word, count, linenum, linenum);

      }
      // if the word is not in the bst, stores each info int temp and inserts it
      // to the bst
      else if (bst.check(word) != true) {
        wordEntry temp;
        temp.word = word;
        temp.count = count;
        temp.numlist.push_back(linenum);
        temp.lastline = linenum;
        bst.SearchTreeInsert(temp);
      }
    }
    // increment line number
    linenum++;
  }
  // call to display
  bst.TraverseDisplay();
  myIn.close(); // close the file
  cout << endl;
  cout << "Thank you for using our program." << endl;
}

// Fucntion used to check for non alphabetic characters to be replaced in the
// program
int isNotAlphaNum(char c) { return !isalnum(c); }