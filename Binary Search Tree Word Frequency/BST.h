

#include "wordEntry.h"
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

typedef string keyType;
class wordEntry;
typedef wordEntry treeItemType;
typedef void (*functionType)(treeItemType &AnItem);

struct treeNode;           // defined in implementation file
typedef treeNode *ptrType; // pointer to node

class bstClass {
public:
  // constructors and destructor:
  bstClass();                     // default constructor
  bstClass(const bstClass &Tree); // copy constructor
  ~bstClass();                    // destructor

  // binary search tree operations:
  // Precondition for all methods: No two items in a binary search tree have the
  // same search key.

  void SearchTreeInsert(const treeItemType &NewItem);
  // Inserts an item into a binary search tree.
  // Precondition: The item to be inserted into the tree is NewItem.
  // Postcondition: If the insertion was successful,
  // NewItem is in its proper order in the tree and
  // Success is true. Otherwise, the tree is unchanged and Success is false.

  void TraverseDisplay();
  // This fucntion prints the header and calls the Display function to display
  // the correct output in the correct format Recursively

  bstClass &operator=(const bstClass &Rhs);
  // overloaded operator =

  bool check(keyType SearchKey);
  // This Function checks for a search key inside the tree by calling checkbst
  // fucntion

  void update(string word, int count, int line, int last);
  // this function takes in the word, could, linenumber and lhe last line of
  // that word and calls updateInfo to update the information of that node with
  // the word in the bst

private:
  // Recursively checks for an item in a binary search tree.
  bool chcekbst(ptrType &TreePtr, keyType key);

  // Recursively checks for an item in a binary search tree and updates its info
  // with the user passed in info.
  void updateInfo(ptrType &TreePtr, string word, int count, int line, int last);

  void InsertItem(ptrType &TreePtr, const treeItemType &NewItem);
  // Recursively inserts an item into a binary search tree.
  // Precondition: TreePtr points to a binary search tree,
  // NewItem is the item to be inserted.
  // Postcondition: Same as SearchTreeInsert.

  void CopyTree(ptrType TreePtr, ptrType &NewTreePtr) const;
  // Used to copy to another TreePointer

  void DestroyTree(ptrType &TreePtr);
  // destroy the tree

  void Display(ptrType TreePtr);
  // Traverses a binary search tree in inorder Recursively and displays each
  // information in the right format

  ptrType Root; // pointer to root of tree
};              // end class
// End of header file.
