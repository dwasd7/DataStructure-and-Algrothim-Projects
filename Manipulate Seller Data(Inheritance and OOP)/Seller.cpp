// implementation file for Seller class

#include "Seller.h"
#include <fstream>
#include <iostream>
#include <list>
using namespace std;

// a default constructor
Seller::Seller() : Person(), Rating("0"), Sold_item("0") {}
// a value constructor that receives all of the data to be placed into the
// data members as its parameters then sets all the data through Parent Classes
// and setting the appropriate info for Seller
Seller::Seller(string fn, string ln, string id, string em, string rating,
               string solditem)
    : Person(fn, ln, id, em), Rating(rating), Sold_item(solditem) {}
// a copy constructor
Seller::Seller(const Seller &onePerson)
    : Person(onePerson), Rating(onePerson.Rating),
      Sold_item(onePerson.Sold_item) {}
//“get” methods to allow the client to obtain information about a PowerSeller
string Seller::getRating() const { return Rating; }

string Seller::getSold_item() const { return Sold_item; }
//“set” methods to allow the client to assign information to a PowerSeller.
void Seller::setRating(string r) { Rating = r; }

void Seller::setSold_item(string num) { Sold_item = num; }

// An overloaded assignment = operator, sets the leftside's object apporopriate
// info to equal the right side object info
void Seller::operator=(const Seller &rhs) {
  Person::operator=(rhs);
  Rating = rhs.Rating;
  Sold_item = rhs.Sold_item;
}

// overloaded << operator To cout all info of the object
ostream &operator<<(ostream &os, const Seller &p) {
  os << p.getFirstName() << endl;
  os << p.getLastName() << endl;
  os << p.getID() << endl;
  os << p.getEmail() << endl;
  os << p.getRating() << endl;
  os << p.getSold_item() << endl;
  return os;
}
// overloaded >> operator To read all info from file to the object
istream &operator>>(istream &is, Seller &p) {
  string fn, ln, id, em;
  string r, num;

  is >> fn >> ln >> id >> em >> r >> num;
  p.setFirstName(fn);
  p.setLastName(ln);
  p.setID(id);
  p.setEmail(em);
  p.setRating(r);
  p.setSold_item(num);
  return is;
}

// a virtual function that displays on screen all the information of a
// Seller by calling Person's Print first then displaying appropriate
// messages
void Seller::print() const {
  Person::print();
  cout << "Average rating: " << Rating << endl;
  cout << "Total items sold: " << Sold_item << endl;
}

// a virtual function that reads in the information of a Seller by first
// calling Person's read from an input then reading the rest
void Seller::read(ifstream &myIn) {
  string r, num;
  Person::read(myIn);
  getline(myIn, r);
  getline(myIn, num);
  Rating = r;
  Sold_item = num;
}
