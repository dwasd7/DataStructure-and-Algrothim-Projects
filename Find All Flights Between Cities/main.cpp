// if late, give reason and pass # here

/*  Author : Diwas Dulal
    Description: This program creates a map object of class to be abel to read
   the number of cities from a data file and Build a adjacency list using
another data file as well and Display gets requests from the request.dat file
and displays thr right output based on wheather there is a path (using various
function) from the original city to the destination city
*/

#include "flightMap.h"
#include <fstream>
#include <iostream>
using namespace std;

int main() {
  FlightMap map; // object for FlightMap class
  ifstream Cities("cities.dat");
  ifstream Flights("flights.dat");

  // Reads cities from cities.dat being passed in
  map.ReadCities(Cities);

  // Reads flight informations and creates a Map from flights.dat being passed
  // in
  map.BuildMap(Flights);

  // Displays it in the correct format
  /// map.DisplayMap();  ///not needed for project 4

  ifstream Requests("requests.dat");
  string scity, ecity; // holds origin city and destination city

  // loops though until it reads all requests and shows appropriate output
  // depending on if the path is found or not
  while (Requests >> scity >> ecity) {
    cout << "Request is to fly from " << scity << " to " << ecity << "."
         << endl;
    if (!map.CheckCity(scity)) { /// if it doesnt serve the starting city than
                                 /// displays this
      cout << "Sorry, BlueSky airline does not serve " << scity << "." << endl;
    } else if (!map.CheckCity(ecity)) { /// if it doesnt serve the ending city
                                        /// than displays this
      cout << "Sorry, BlueSky airline does not serve " << ecity << "." << endl;
    } else /// other wise find the path and dispays it within the function
    {
      map.FindPath(scity, ecity);
      cout << endl;
    }
  }

  Cities.close();
  Flights.close();
  Requests.close();
  return 0;
}