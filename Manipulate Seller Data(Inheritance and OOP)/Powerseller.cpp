// implementation file for Powerseller class

#include "Powerseller.h"
#include <fstream>
#include <iostream>
#include <list>
using namespace std;

// a default constructor
PowerSeller::PowerSeller()
    : Seller(), Website("No Website"), Sold_item_year("No Sold Item Year") {}
// a value constructor that receives all of the data to be placed into the
// data members as its parameters then sets all the data through Parent Classes
// and setting the appropriate info for PowerSeller
PowerSeller::PowerSeller(string fn, string ln, string id, string em,
                         string rating, string solditem, string web,
                         string solditemyear)
    : Seller(fn, ln, id, em, rating, solditem), Website(web),
      Sold_item_year(solditemyear) {}
// a copy constructor
PowerSeller::PowerSeller(const PowerSeller &onePerson)
    : Seller(onePerson), Website(onePerson.Website),
      Sold_item_year(onePerson.Sold_item_year) {}

//“get” methods to allow the client to obtain information about a PowerSeller
string PowerSeller::getWebsite() const { return Website; }
string PowerSeller::getSold_item_year() const { return Sold_item_year; }

//“set” methods to allow the client to assign information to a PowerSeller.
void PowerSeller::setWebsite(string web) { Website = web; }
void PowerSeller::setSold_item_year(string solditemyear) {
  Sold_item_year = solditemyear;
}

// An overloaded assignment = operator, sets the leftside's object apporopriate
// info to equal the right side object info
void PowerSeller::operator=(const PowerSeller &rhs) {
  Seller::operator=(rhs);
  Website = rhs.Website;
  Sold_item_year = rhs.Sold_item_year;
}

// overloaded << operator To cout all info of the object
ostream &operator<<(ostream &os, const PowerSeller &p) {
  os << p.getFirstName() << endl;
  os << p.getLastName() << endl;
  os << p.getID() << endl;
  os << p.getEmail() << endl;
  os << p.getRating() << endl;
  os << p.getSold_item() << endl;
  os << p.getWebsite() << endl;
  os << p.getSold_item_year() << endl;

  return os;
}

// overloaded >> operator To read all info from file to the object
istream &operator>>(istream &is, PowerSeller &p) {
  string fn, ln, id, em, web, solditemyear;
  string r, num;

  is >> fn >> ln >> id >> em >> r >> num >> web >> solditemyear;
  p.setFirstName(fn);
  p.setLastName(ln);
  p.setID(id);
  p.setEmail(em);
  p.setRating(r);
  p.setSold_item(num);
  p.setWebsite(web);
  p.setSold_item_year(solditemyear);
  return is;
}

// a virtual function that displays on screen all the information of a
// PowerSeller by calling Seller's Print first then displaying appropriate
// messages
void PowerSeller::print() const {
  Seller::print();
  cout << "Website: " << Website << endl;
  cout << "Current Sale: " << Sold_item_year << endl;

} // VIRTUAL can be OVERRIDED in the Inheritance Classes

// a virtual function that reads in the information of a PowerSeller by first
// calling seller's read from an input then reading the rest
void PowerSeller::read(ifstream &myIn) {
  string web, solditemyear;
  Seller::read(myIn);
  getline(myIn, web);
  getline(myIn, solditemyear);
  Website = web;
  Sold_item_year = solditemyear;
} // VIRTUAL can be OVERRIDED in the Inheritance Classes
