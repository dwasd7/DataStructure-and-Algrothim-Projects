#include "flightMap.h"
#include <cassert>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
using namespace std;

FlightMap::FlightMap() {
  size = 0;
  map = NULL;
}
// copy constructor
FlightMap::FlightMap(const FlightMap &flight) {
  size = flight.size; // get the size and copys it
  for (int i = 0; i < size; i++)
    cities.push_back(flight.cities[i]); // copy the cities

  // dynamic allocation
  map = new list<flightRec>[size];

  // copies flight map
  for (int i = 0; i < size; i++)
    map[i] = flight.map[i];
}

// Destructor which deallocats the memory
FlightMap::~FlightMap() { delete[] map; }

// Read cities from a data file
// Pre-condition: Input stream is provided
// Post-condition: Data file is read
//				  Cities are in ascending order
void FlightMap::ReadCities(ifstream &myCities) {
  string tempCity; // temp for each city
  int i;
  myCities >> size;

  for (i = 0; i < size; i++) {
    myCities >> tempCity;
    cities.push_back(tempCity);
  }
}

// Reads flight information and build the adjacency list
// Pre-condition: list of the flight information is provided
// Post-condition: Flight map is built
void FlightMap::BuildMap(ifstream &myFlights) {
  // Variables Decleration to hold data from the file and also create a temp
  // flightRec
  map = new list<flightRec>[size];
  int flightNum, price;
  string origin, destination;
  flightRec temp;

  // read info from the data file and store it in a temp struct type of flight
  // Record
  while (myFlights >> flightNum >> origin >> destination >> price) {
    temp.flightNum = flightNum;
    temp.origin = origin;
    temp.destination = destination;
    temp.price = price;

    // it goes through the cities list
    // and looks for the city that matches with the current city
    for (int i = 0; i < size; i++) {
      // if found the city that matches,
      if (temp.origin == cities[i]) {
        // then insert the current record
        // and link it with the current city
        map[i].push_back(temp);
      }
    }
  }

  for (int i = 0; i < size; i++)
    map[i].sort(); // uses the overloaded operatro "<" for the sort
}

// Displays the the map created in the correct format provide in the output
// example using overloaded << opererator Pre-condition: none Post-condition:
// Flight map is displayed
void FlightMap::DisplayMap() {
  list<flightRec> CityList; // city's list
  flightRec flight;         // current flight information

  cout << setw(19) << "Origin" << setw(21) << "Destination" << setw(8)
       << "Flight" << setw(7) << "Price" << endl;
  cout << "========================================================" << endl;

  // This loops displays the map
  for (int i = 0; i < size; i++) {
    // this goes pass the city if the origin has no flights
    if (map[i].size() == 0)
      continue;
    else {
      cout << " From " << setw(13) << cities[i] << " to:";
      CityList = map[i];
      int j = 0;
      list<flightRec>::iterator k;

      for (k = map[i].begin(); k != map[i].end(); k++) {

        flight = *k; // current record

        // Displays in the right format
        if (j == 0) {
          cout << setw(17) << flight.destination << setw(8) << flight.flightNum
               << setw(4) << "$" << setw(3) << flight.price << endl;
          j++;
        } else {
          cout << setw(40) << flight.destination << setw(8) << flight.flightNum
               << setw(4) << "$" << setw(3) << flight.price << endl;
        }
      }
    }
  }
}

// Check whether a city is in the cities that BlueSky airline serves.
// Pre-condition: cityNumber to be checked is provided
// Post-condition: return true if the city is in the cities array
//              otherwise return false
bool FlightMap::CheckCity(string cityName) const {
  bool found = false;
  /// loops and if the city is there then makes found true else stays false and
  /// returns it
  for (int i = 0; i < size; i++) {
    if (cityName == cities[i])
      found = true;
  }

  return found;
}

// Displays all of the cities
void FlightMap::DisplayAllCities() const {
  /// loops and displays every city
  for (int i = 0; i < size; i++)
    cout << cities[i] << endl;
}

// Marks a city as visited
// Pre-condition: city to be marked as visited is provided
// Post-condition: a city is marked as visited
void FlightMap::MarkVisited(int city) {
  visited[city] = true; /// makes the city visited
}

// Clears marks on all cities
// Pre-condition: there are > 0 cities in a cities array
// Post-condition: all cities marked as unvisited
void FlightMap::UnvisitAll() {
  /// loops through the visited list and makes everything false or unvisited
  if (visited.size() == 0) {
    for (int i = 0; i < size; i++)
      visited.push_back(false);
  } else
    for (int j = 0; j < size; j++)
      visited[j] = false;
}

// Determines whether a city was visited
// Pre-condition: city is provided
// Post-condition: return true if city has been visited
//              otherwise return false
bool FlightMap::IsVisited(int city) const {
  return visited[city]; /// returns true if visited else false
}

// Determines the next unvisited city, if any,
// that is adjacent to a given city.
// success indicates whether an unvisited adjacent city was found
// Pre-condition: topCity and nextCity provided
// Post-condition: return true if an unvisited adjacent city was found
//              otherwise return false
bool FlightMap::GetNextCity(string fromCity, string &nextCity) {
  list<flightRec>
      adjList;        /// this is the list of all flights in a adjacency List
  flightRec flight;   /// this holds each flight
  string destCity;    /// this holds destinaton city
  bool found = false; /// checks if it is found or not
  list<flightRec>::iterator itr;
  adjList = map[GetCityNumber(
      fromCity)]; /// this holds the list of all flights in a adjacency List
  /// loops through to check unvisited in the list
  for (itr = adjList.begin(); itr != adjList.end(); itr++) {
    /// this holds 1 flight as it loops thoughout the adjList
    flight = *itr;
    destCity = flight.destination;

    /// if the adj destcity is not visited gets out of the loop
    if (!visited[GetCityNumber(destCity)]) {
      found = true;
      break;
    }
  }

  /// if an unvisited is found than sets nextcity to destcity
  if (found) {
    nextCity = destCity;
  }

  // returns found
  return found;
}

// returns the integer index corresponding to a city name
// Pre-condition: name of a city is provided
// Post-condition: returns the index number corresponding to a city name
int FlightMap::GetCityNumber(string cityName) const {
  int num;
  /// this searches for the right city number and sets num eqaul to the index
  /// and returns it
  for (int i = 0; i < size; i++) {
    if (cities[i] == cityName)
      num = i;
  }
  return num;
}

// returns the name of a city given its corresponding index
// Pre-condition: number of a city is provided
// Post-condition: returns the city's name
string FlightMap::GetCityName(int cityNumber) const {
  return cities[cityNumber]; // returns the name
}

// Determines whether a sequence of flights between two cities exists.
// Pre-condition: originCity and destinationCity are the origin and destination
// city, respectively Post-condition: returns true if a sequence of flights
// exists
//              from origin to destination; otherwise return false.
//              Cities visited during the search are marked as visited
//              in the flight map.
void FlightMap::FindPath(string originCity, string destinationCity) {
  /// holds topcity on stack and the next
  string topCity;
  string nextCity;

  string temp; /// temporary
  bool found;
  int tot = 0;                  /// this holds the total price
  stack<string> itineraryStack; /// this holds the itinerary
  stack<string> reverseStack;   /// this holds the itinerary in reverse
  UnvisitAll();                 /// Makes all cites  unvisited

  /// this pushs origin city on top of the itineraryStack then makes it so it
  /// is visitied
  itineraryStack.push(originCity);
  MarkVisited(GetCityNumber(originCity));

  /// gets the top of the stack
  topCity = itineraryStack.top();

  /// loops though where the stack holds the path of the city from start at
  /// the bottom to the end on top then looks for an unvisited city starting
  /// from the top
  while (!itineraryStack.empty() && (topCity != destinationCity)) {
    found = GetNextCity(topCity, nextCity);
    /// if not found then it goes back
    if (!found) {
      itineraryStack.pop();
    }
    /// else visits the city
    else {
      itineraryStack.push(nextCity);
      MarkVisited(GetCityNumber(nextCity));
    }
    if (!itineraryStack.empty()) {
      topCity = itineraryStack.top();
    }
  }

  /// this means that there is no path from the originCity to destinationCity
  /// and reports the right message
  if (itineraryStack.size() == 0) {
    cout << "Sorry, BlueSky airline does not fly from " << originCity << " to "
         << destinationCity << "." << endl;
  } else /// if these is a path then it displays the right message
  {
    list<flightRec>
        adjList;      /// this is the list of all flights in a adjacency List
    flightRec flight; /// this holds each flight

    /// this prints the top layout
    cout << "The flight itinerary is:" << endl;
    cout << "Flight #" << setw(15) << "From" << setw(15) << "To" << setw(7)
         << "Cost" << endl;

    /// makes it reverse order
    while (!itineraryStack.empty()) {
      temp = itineraryStack.top(); /// gets it from the top
      itineraryStack.pop();        /// pops the top
      reverseStack.push(temp);     /// pushes it on the reverse stack
    }

    /// holds the original city and end destination city
    string scity; /// original city
    string ecity; /// destination city

    scity = reverseStack.top();
    reverseStack.pop();

    /// lops though and chance the adjList while changing temp city
    while (!reverseStack.empty()) {
      adjList = map[GetCityNumber(scity)];

      /// gets the next destination city's number
      ecity = reverseStack.top();
      reverseStack.pop();

      list<flightRec>::iterator itr;
      for (itr = adjList.begin(); itr != adjList.end(); itr++) {
        flight = *itr; /// this holds 1 flight as it loops thoughout the adjList
        /// if the current flight in the loop is equal to the end city then it
        /// displays the flight's inforamtion
        if (flight.destination == ecity) {
          cout << setw(8) << flight.flightNum << setw(15) << flight.origin
               << setw(15) << flight.destination << setw(3) << "$" << setw(4)
               << flight.price << endl;

          tot = tot + flight.price;

          /// this sets the start city's number to the current flight's
          scity = flight.destination;
          break;
        }
      }
    }
    /// displays the total
    cout << setw(38) << "Total:" << setw(3) << "$" << setw(4) << tot << endl;
  }
}