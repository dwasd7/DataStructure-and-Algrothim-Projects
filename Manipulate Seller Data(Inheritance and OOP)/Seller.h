// header file for Seller class

#include "Person.h"
#include <fstream>
#include <iostream>
using namespace std;

#ifndef SELLER_H
#define SELLER_H

using namespace std;

class Seller : public Person {

public:
  // a default constructor
  Seller();
  // a value constructor that receives all of the data to be placed into the
// data members as its parameters then sets all the data through Parent Classes and setting the appropriate info for Seller
  Seller(string, string, string, string, string, string);
  // a copy constructor
  Seller(const Seller &onePerson);
//“get” methods to allow the client to obtain information about a PowerSeller
  string getRating() const;

  string getSold_item() const;
//“set” methods to allow the client to assign information to a PowerSeller.
  void setRating(string);

  void setSold_item(string);

  // An overloaded assignment = operator, sets the leftside's object apporopriate
// info to equal the right side object info
  void operator=(const Seller &rhs);

  // overloaded << operator To cout all info of the object
  friend ostream &operator<<(ostream &os, const Seller &p);

  // overloaded >> operator To read all info from file to the object
  friend istream &operator>>(istream &is, Seller &p);

// a virtual function that displays on screen all the information of a
// Seller by calling Person's Print first then displaying appropriate
// messages
  void print() const override; /// VIRTUAL from base class can be OVERRIDED in
                               /// the Inheritance Classes

// a virtual function that reads in the information of a Seller by first
// calling Person's read from an input then reading the rest
  void read(ifstream &myIn) override; // VIRTUAL from base class can be
                                      // OVERRIDED in the Inheritance Classes

private:
  string Rating;    // average star rating received from the buyers
  string Sold_item; // total number of items sold
};

#endif