// header file for Powerseller class
#include "Seller.h"
#include <fstream>
#include <iostream>
#include <list>
using namespace std;

#ifndef POWERSELLER_H
#define POWERSELLER_H

using namespace std;
class PowerSeller : public Seller {

public:
  // a default constructor
  PowerSeller();
  // a value constructor that receives all of the data to be placed into the
// data members as its parameters then sets all the data through Parent Classes and setting the appropriate info for PowerSeller
  PowerSeller(string, string, string, string, string, string, string, string);
  // a copy constructor
  PowerSeller(const PowerSeller &onePerson);
  //“get” methods to allow the client to obtain information about a PowerSeller
  string getWebsite() const;

  string getSold_item_year() const;
  //“set” methods to allow the client to assign information to a PowerSeller.
  void setWebsite(string);

  void setSold_item_year(string);

  // An overloaded assignment = operator, sets the leftside's object
  // apporopriate info to equal the right side object info
  void operator=(const PowerSeller &rhs);

  // overloaded << operator To cout all info of the object
  friend ostream &operator<<(ostream &os, const PowerSeller &p);

  // overloaded >> operator To read all info from file to the object
  friend istream &operator>>(istream &os, PowerSeller &p);
  // a virtual function that displays on screen all the information of a
  // PowerSeller by calling Seller's Print first then displaying appropriate
  // messages
  void print() const override; /// VIRTUAL from base class can be OVERRIDED in
                               /// the Inheritance Classes
  // a virtual function that reads in the information of a PowerSeller by first
  // calling seller's read from an input then reading the rest
  void read(ifstream &myIn) override; // VIRTUAL from base class can be
                                      // OVERRIDED in the Inheritance Classes
private:
// Private Variables
  string Website;
  string Sold_item_year;
};

#endif
