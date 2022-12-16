// implementation file for Person class
#include "Person.h"
#include <fstream>
#include <iostream>
#include <list>
#include <string>

// a default constructor
Person::Person() {
  FirstName = "No First Name";
  LastName = "No Last Name";
  ID = "No ID";
  Email = "No Email";
}
// a value constructor that receives all of the data to be placed into the
// data members as its parameters
Person::Person(string fName, string lName, string Id, string email) {
  FirstName = fName;
  LastName = lName;
  ID = Id;
  Email = email;
}
// a copy constructor
Person::Person(const Person &onePerson) {
  setFirstName(onePerson.getFirstName());
  setLastName(onePerson.getLastName());
  setID(onePerson.getID());
  setEmail(onePerson.getEmail());
}
//“get” methods to allow the client to obtain information about a person
string Person::getFirstName() const { return FirstName; }
string Person::getLastName() const { return LastName; }
string Person::getID() const { return ID; }
string Person::getEmail() const { return Email; }
//“set” methods to allow the client to assign information to a person.
void Person::setFirstName(string fn) { FirstName = fn; }
void Person::setLastName(string ln) { LastName = ln; }
void Person::setID(string id) { ID = id; }
void Person::setEmail(string email) { Email = email; }

// overloaded operators

// overloaded == method that returns true if two sellers have identical names
// and email address; otherwise it returns false.
bool Person::operator==(const Person &rhs) const {
  return (FirstName == rhs.FirstName && LastName == rhs.LastName &&
          Email == rhs.Email);
}
// overloaded !=, <, and > operators (for > and < operators, comparisons are
// based on last names)
bool Person::operator!=(const Person &rhs) const {
  return (LastName != rhs.LastName);
}
bool Person::operator<(const Person &rhs) const {
  return (LastName < rhs.LastName);
}
bool Person::operator>(const Person &rhs) const {
  return (LastName > rhs.LastName);
}

// An overloaded assignment = operator, sets the leftside's object apporopriate
// info to equal the right side object info
void Person::operator=(const Person &rhs) {
  FirstName = rhs.FirstName;
  LastName = rhs.LastName;
  ID = rhs.ID;
  Email = rhs.Email;
}

// To cout all info of the object
ostream &operator<<(ostream &os, const Person &p) {
  os << p.FirstName << endl;
  os << p.LastName << endl;
  os << p.ID << endl;
  os << p.Email << endl;
  return os;
}
// To read all info from file to the object
istream &operator>>(istream &is, Person &p) {
  string fn, ln, id, em;
  is >> fn >> ln >> id >> em;
  p.setFirstName(fn);
  p.setLastName(ln);
  p.setID(id);
  p.setEmail(em);
  return is;
}

// a virtual function that displays on screen all the information of a person
// with appropriate messages
void Person::print() const {
  cout << "Name: " << getFirstName() << " " << getLastName() << endl;
  cout << "User ID: " << getID() << endl;
  cout << "Email: " << getEmail() << endl;
}
// a virtual function that reads in the information of a Person from an input
void Person::read(ifstream &myIn) {
  /// NOT SURE to use >> Operator or this
  string fn, ln, id, em;
  getline(myIn, fn);
  getline(myIn, ln);
  getline(myIn, id);
  getline(myIn, em);
  FirstName = fn;
  LastName = ln;
  ID = id;
  Email = em;
}