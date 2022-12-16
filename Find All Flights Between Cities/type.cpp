#include "type.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// Define the overloaded methods for struct type here

// implement the overloaded operator
// declare overloaded < operator for flightRec
  // this function compares the destinations between two flightRec
bool flightRec::operator<(const flightRec &rhs) const {
  return (destination < rhs.destination);
}

// implement the overloaded operator
// declare overloaded == operator for flightRec
  // this function compares the origins and destinations between two flightRec
bool flightRec::operator==(const flightRec &rhs) const {
  return ((origin == rhs.origin) && (destination == rhs.destination));
}

  // declare overloaded << (insertion) operator for flightRec struct
ostream &operator<<(ostream &os, const flightRec &f) {
  // prints out all the information in the right format
  os << setw(15) << f.origin << setw(15) << f.destination << setw(10)
     << f.flightNum << setw(4) << "$" << setw(3) << f.price << endl;

  return os;
}