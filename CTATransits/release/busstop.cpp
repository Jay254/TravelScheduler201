/*busstops.cpp*/

#include <string>
#include <vector>
#include <iostream>

#include "busstop.h"
// #include "node.h"
// #include "nodes.h"

using namespace std;

//
// Default constructor
//
BusStop::BusStop()
{
}

//
// Parameterized constructor
//
// Initializes a BusStop object with specific information.
BusStop::BusStop(int stopID, int busRoute, string stopName, string travelDirection, string stopLoc, double lat, double lon)
    : stopID(stopID), busRoute(busRoute), stopName(stopName), travelDirection(travelDirection), stopLocation(stopLoc), lat(lat), lon(lon)
{
}

//
// print
//
// prints out all the bus stops
void BusStop::print()
{
    cout << this->stopID << ": bus " << this->busRoute << ", " << this->stopName << ", " << this->travelDirection << ", " << this->stopLocation << ", location (" << this->lat << ", " << this->lon << ")" << endl;
}