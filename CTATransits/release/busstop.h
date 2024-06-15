/*busstop.h*/

// a busstop in the Open Street Map.

// <<JAY KIPTOO YEGON>>
// <<COMPUTER SCIENCE AND ENGINEERING MAJOR>>

#pragma once

#include <string>
#include <vector>

#include "node.h"
#include "nodes.h"

using namespace std;

class BusStop
{
public:
    // member variables for a bus stop
    int stopID, busRoute;
    string stopName, travelDirection, stopLocation;
    double lat, lon;

    BusStop();
    //
    // Constructor
    //
    BusStop(int stopID, int busRoute, string stopName, string travelDirection, string stopLocation, double lat, double lon);

    //
    // print
    //
    // prints out a bus stop
    void print();
};