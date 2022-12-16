// if late, give reason and pass # here
/*
 PROGRAMMER: Diwas Dulal
 Program Description:
  This program uses Inheretiance and has classes that goes from Person class, to
 Seller class, to PowerSeller class but first reads data from sellers.dat file
 and stores it in a STL list where you are able to add other PowerSeller or
 regurlar Seller. Client can also delete a seller, check the information of a
 seller and print the list as sellers.
*/
#include "Person.h"
#include "Powerseller.h"
#include "Seller.h"
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
using namespace std;

// function prototypes
void CreateList(ifstream &myIn);
void DisplayMenu();
void PrintInfo();
void CheckInfo();
void AddSeller();
void RemoveSeller();

list<Seller *> allsellers; // stl list of pointers to object Seller

int main() {
  ifstream myIn("sellers.dat");
  assert(myIn);
  string choice; // user choice
  bool done = false;
  CreateList(myIn);

  // loop though while user is not done
  while (done == false) {
    DisplayMenu(); // Displays the Menu
    cout << " Enter your choice: ";
    cin >> choice;
    cout << endl;

    if (choice == "1") {
      PrintInfo(); // print the list of all Player's information
    } else if (choice == "2") {
      CheckInfo(); // prints the info of a certain Seller chosen by the user by
                   // checking if its in the list
    } else if (choice == "3") {
      AddSeller(); // Adds a seller infprotion to the list depending on the user
                   // input
    } else if (choice == "4") {
      RemoveSeller(); // Removes the Seller depending on the user choice
    } else if (choice == "5") {
      // prints if the choice is 5 or something else
      done = true;
      cout << endl;
      cout << "Thank you for using Sellers n Stuff" << endl;
    } else {
      // If user picked a choice that is not in the menu

      cout << "INVALID CHOICE, TRY AGAIN!" << endl << endl;
      continue;
    }
    cout << endl;
  }
  myIn.close();
  return 0;
}
// prints all the info of all the sellers
void PrintInfo() {
  list<Seller *>::iterator itr;
  for (itr = allsellers.begin(); itr != allsellers.end(); itr++) {
    (*itr)->print();
    cout << endl;
  }
}
// prints the info of a certain Seller chosen by the user by checking if its in
// the list
void CheckInfo() {
  string fname, lname; // fisrt and lastname variable
  cout << "Enter first name: ";
  cin >> fname;
  cout << "Enter last name: ";
  cin >> lname;
  cout << endl;
  list<Seller *>::iterator itr;
  // this loop goes through the list and checks of the first name given by the
  // user and the last name given by the user matches one of the seller or not
  // and prints that seller's informataion if it is
  for (itr = allsellers.begin(); itr != allsellers.end(); itr++) {
    if ((*itr)->getFirstName() == fname || (*itr)->getLastName() == lname) {
      (*itr)->print();
      return;
    }
  }
  cout << "No Seller Found Of That Name!" << endl;
}

// Removes the Seller depending on the user choice
void RemoveSeller() {
  string fname, lname; // fisrt and lastname variable
  cout << "Enter first name: ";
  cin >> fname;
  cout << "Enter last name: ";
  cin >> lname;
  cout << endl;
  list<Seller *>::iterator itr;
  // this loop goes through and deletes the seller that user inputs and
  // dellocates the memory space for it
  for (itr = allsellers.begin(); itr != allsellers.end(); itr++) {
    if ((*itr)->getFirstName() == fname || (*itr)->getLastName() == lname) {
      allsellers.remove((*itr)); // remove the seller from the list
      delete (*itr);             // delocate space
      cout << "SELLER REMOVED FROM THE LIST" << endl;
      return;
    }
  }
  cout << "No Seller Found Of That Name!" << endl;
}

void AddSeller() {
  ////variables to store all the seller info given by the user
  string fn, ln, id, em, r, num, web, solditemyear, sellertype;
  Seller *sptr;       // pointer for Seller Object
  PowerSeller *psptr; // pointer for PowerSeller Object
  cout << "Please enter the following information (enter invalid type to quit):"
       << endl
       << endl;
  cout << "Is the seller a (S)eller or (P)ower Seller? ";
  cin >> sellertype;
  // if the user picks "P" or "S"
  if (sellertype == "P" || sellertype == "S") {
    // gets all the seller info
    cout << "First name: ";
    cin >> fn;
    cout << "Last name: ";
    cin >> ln;
    cout << "User ID: ";
    cin >> id;
    cout << "Email Address: ";
    cin >> em;
    cout << "Average Star Rating: ";
    cin >> r;
    cout << "Total Items sold: ";
    cin >> num;
    // if sellertype is a Power seller, it gets the apporiate powerseller info
    if (sellertype == "P") {
      cout << "Website Address: ";
      cin >> web;
      cout << "Current year products Sold: ";
      cin >> solditemyear;
      // creates a new object with the apporiate informtaion
      psptr = new PowerSeller(fn, ln, id, em, r, num, web, solditemyear);
      allsellers.push_back(
          psptr); // pushes the pointer to that object back of the list
      cout << endl;
      cout << " The new Power Seller has been added.  Returning to Seller "
              "management... "
           << endl;
    } else {
      // creates a new object with the apporiate informtaion
      sptr = new Seller(fn, ln, id, em, r, num);
      allsellers.push_back(
          sptr); // pushes the pointer to that object back of the list
      cout << endl;
      cout << " The new Seller has been added.  Returning to Seller "
              "management... "
           << endl;
    }
    cout << endl;
  }
}
// This fucntion displays the Menu Information about the
void DisplayMenu() {
  cout << "PLease choose from the following menu: " << endl;
  cout << "1. Print all seller information " << endl;
  cout << "2. Check information of one seller " << endl;
  cout << "3. Add a seller " << endl;
  cout << "4. Remove a seller " << endl;
  cout << "5. Quit " << endl;
}

// This fucntion takes in the seller.dat file as myIn and loops thorugh and
// creates a new Seller Object depending on "P" or "S" and reads the information
// to that Object and pushes the pointer to those Object to the back of the list
void CreateList(ifstream &myIn) {
  // STL list of allsellers
  Seller *sptr;       // Pointer to Seller Object
  PowerSeller *psptr; // Pointer to PowerSeller Object
  string line;
  // loops through and gets the line and if the list is "S" or "P" creats the
  // apporiate Object and reads it and adds the pointer the object to the list
  while (getline(myIn, line)) {
    // if the list is "S", creats the apporiate Object and reads it and adds the
    // pointer the object to the list
    if (line == "S") {
      sptr = new Seller;
      (*sptr).read(myIn);
      allsellers.push_back(sptr);
    }
    // else if the list is "P", creats the apporiate Object and reads it and
    // adds the pointer the object to the list
    else {
      psptr = new PowerSeller;
      (*psptr).read(myIn);
      allsellers.push_back(psptr);
    }
  }
}
