
#include "BST.h"
#include "wordEntry.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

struct treeNode {
  treeItemType Item;
  ptrType LChildPtr, RChildPtr;

  // constructor:
  treeNode(const treeItemType &NodeItem, ptrType L, ptrType R);
}; // end struct

treeNode::treeNode(const treeItemType &NodeItem, ptrType L, ptrType R)
    : Item(NodeItem), LChildPtr(L), RChildPtr(R) {} // end constructor

bstClass::bstClass() : Root(NULL) {} // end default constructor

// copy constructor
bstClass::bstClass(const bstClass &Tree) {
  CopyTree(Tree.Root, Root);
} // end copy constructor

// destructor
bstClass::~bstClass() { DestroyTree(Root); } // end destructor

// Inserts an item into a binary search tree.
// Precondition: The item to be inserted into the tree is NewItem.
// Postcondition: If the insertion was successful,
// NewItem is in its proper order in the tree and
// Success is true. Otherwise, the tree is unchanged and Success is false.
void bstClass::SearchTreeInsert(const treeItemType &NewItem) {
  InsertItem(Root, NewItem);
} // end SearchTreeInsert

// This fucntion prints the header and calls the Display function to display the
// correct output in the correct format Recursively

void bstClass::TraverseDisplay() {
  cout << "--------------------------------------------------------------------"
          "---"
       << endl;
  cout << left << setw(20) << "Word" << setw(20) << "Frequency" << setw(20)
       << "Occurs on Lines" << endl;
  cout << "--------------------------------------------------------------------"
          "---"
       << endl;
  Display(Root);
}

// Recursively inserts an item into a binary search tree.
// Precondition: TreePtr points to a binary search tree,
// NewItem is the item to be inserted.
// Postcondition: Same as SearchTreeInsert.
void bstClass::InsertItem(ptrType &TreePtr, const treeItemType &NewItem) {
  if (TreePtr == NULL) { // position of insertion found; insert after leaf

    // create a new node
    TreePtr = new treeNode(NewItem, NULL, NULL);
  }

  // else search for the insertion position
  else if (NewItem.Key() < TreePtr->Item.Key())
    // search the left subtree
    InsertItem(TreePtr->LChildPtr, NewItem);

  else // search the right subtree
    InsertItem(TreePtr->RChildPtr, NewItem);
} // end InsertItem

// This Function checks for a search key inside the tree by calling checkbst
// fucntion

bool bstClass::check(keyType SearchKey) { return chcekbst(Root, SearchKey); }

// this function takes in the word, could, linenumber and lhe last line of
// that word and calls updateInfo to update the information of that node with
// the word in the bst
void bstClass::update(string word, int count, int line, int last) {
  updateInfo(Root, word, count, line, last);
}

// Recursively checks for an item in a binary search tree.
bool bstClass::chcekbst(ptrType &TreePtr, keyType SearchKey) {
  if (TreePtr == NULL) {
    // if root is null then return false since it was not found
    return false;
  }
  if (SearchKey == TreePtr->Item.Key()) { // item is in the root of some subtree
    return true;                          // return true
  }

  // else search for the item
  else if (SearchKey < TreePtr->Item.Key())
    // search the left subtree
    return chcekbst(TreePtr->LChildPtr, SearchKey);

  else // search the right subtree
    return chcekbst(TreePtr->RChildPtr, SearchKey);
  return false;
}

// Recursively checks for an item in a binary search tree and updates its info
// with the user passed in info.
void bstClass::updateInfo(ptrType &TreePtr, string SearchKey, int count,
                          int line, int last) {
  bool visited = false; // used to check if linenumber is in the list or not
  if (SearchKey == TreePtr->Item.Key()) { // item is in the root of some subtree
    TreePtr->Item.count += count;
    list<int>::iterator it;

    // this loop goes through each linenumber in the list numlist and see if the
    // linenumber for the current word is already in the list or not and if it is
    // in the list then makes visited true and breaks out
    for (it = TreePtr->Item.numlist.begin(); it != TreePtr->Item.numlist.end();
         it++) {
      // if linenumber is in the list then it has been visited and breaks out
      if ((*it) == line) {
        visited = true;
        break;
      }
    }
    // only if visited was false, it adds the linenumber the word was found in
    // in the list
    if (visited == false) {
      TreePtr->Item.numlist.push_back(line);
    }

    // add the last linenumber in the lastline variable
    TreePtr->Item.lastline = last;
    return;
  } // end if in root

  // else search for the item
  else if (SearchKey < TreePtr->Item.Key())
    // search the left subtree
    updateInfo(TreePtr->LChildPtr, SearchKey, count, line, last);

  else // search the right subtree
    updateInfo(TreePtr->RChildPtr, SearchKey, count, line, last);
}

bstClass &bstClass::operator=(const bstClass &Rhs) {
  if (this != &Rhs) {
    DestroyTree(Root);        // deallocate left-hand side
    CopyTree(Rhs.Root, Root); // copy right-hand side
  }                           // end if
  return *this;
} // end operator=

// Used to copy to another TreePointer
void bstClass::CopyTree(ptrType TreePtr, ptrType &NewTreePtr) const {
  // preorder traversal
  if (TreePtr != NULL) { // copy node
    NewTreePtr = new treeNode(TreePtr->Item, NULL, NULL);
    assert(NewTreePtr != NULL);

    CopyTree(TreePtr->LChildPtr, NewTreePtr->LChildPtr);
    CopyTree(TreePtr->RChildPtr, NewTreePtr->RChildPtr);
  } // end if
  else
    NewTreePtr = NULL; // copy empty tree
} // end CopyTree

// destroy the tree
void bstClass::DestroyTree(ptrType &TreePtr) {
  // postorder traversal
  if (TreePtr != NULL) {
    DestroyTree(TreePtr->LChildPtr);
    DestroyTree(TreePtr->RChildPtr);
    delete TreePtr;
    TreePtr = NULL;
  } // end if
} // end DestroyTree

// Traverses a binary search tree in inorder Recursively and displays each
// information in the right format
void bstClass::Display(ptrType TreePtr) {
  list<int> mylist;
  if (TreePtr != NULL) {
    Display(TreePtr->LChildPtr);
    cout << left << setw(20) << TreePtr->Item.word << setw(20)
         << TreePtr->Item.count;

    mylist = TreePtr->Item.numlist;

    // this loop goes though the numlist of each node and prints it out until
    // the second last line number
    for (auto it = mylist.begin(); it != prev(mylist.end()); ++it) {
      cout << (*it) << ", ";
    }

    // prints the last line number to have the correct format of the output
    cout << TreePtr->Item.lastline << endl;
    Display(TreePtr->RChildPtr);
  } // end if
} // end Inorder
