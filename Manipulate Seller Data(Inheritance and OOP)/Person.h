// header file for Person class
#include <fstream>
#include <iostream>
#include <list>
#include <string>
using namespace std;

#ifndef PERSON_H
#define PERSON_H

using namespace std;
class Person {
public:
  // a default constructor
  Person();
  // a value constructor that receives all of the data to be placed into the
  // data members as its parameters
  Person(string, string, string, string);
  // a copy constructor
  Person(const Person &onePerson);
  //“get” methods to allow the client to obtain information about a person
  string getFirstName() const;
  string getLastName() const;
  string getID() const;
  string getEmail() const;
  //“set” methods to allow the client to assign information to a seller.
  void setFirstName(string);
  void setLastName(string);
  void setID(string);
  void setEmail(string);

  // overloaded operators

  // overloaded == method that returns true if two sellers have identical names
  // and email address; otherwise it returns false.
  bool operator==(const Person &rhs) const;
  // overloaded !=, <, and > operators (for > and < operators, comparisons are
  // based on last names)
  bool operator!=(const Person &rhs) const;

  bool operator<(const Person &rhs) const;

  bool operator>(const Person &rhs) const;

  // An overloaded assignment = operator ??
  void operator=(const Person &rhs);

  // To cout all info of the object
  friend ostream &operator<<(ostream &os, const Person &p);

  // To read all info from file to the object
  friend istream &operator>>(istream &os, Person &p);

  // a virtual function that displays on screen all the information of a person
  // with appropriate messages
  virtual void
  print() const; // VIRTUAL can be OVERRIDED in the Inheritance Classes
  // a virtual function that reads in the information of a Person from an input
  // file stream Consider which of these methods should be const method?
  virtual void
  read(ifstream &myIn); // VIRTUAL can be OVERRIDED in the Inheritance Classes

private:
  // Private Variables
  string FirstName;
  string LastName;
  string ID;
  string Email;
};

#endif