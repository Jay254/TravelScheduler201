/*busstops.h*/

// busstops in the Open Street Map.

// <<JAY KIPTOO YEGON>>
// <<COMPUTER SCIENCE AND ENGINEERING MAJOR>>

#pragma once

#include <string>
#include <vector>
#include "dist.h"

#include "busstop.h"
#include "curl_util.h"
// #include "building.h"
// #include "node.h"
// #include "nodes.h"

using namespace std;

class BusStops
{
public:
    // string filename;
    vector<BusStop> Busstops;
    //
    // Constructor
    //
    BusStops(string filename);

    //
    // printAllBusStops
    //
    // prints out all the bus stops
    void printAllBusStops();

    //
    // closestStops
    //
    // finds the closest bus southbound and northbound stops to a given location
    void closestStops(double lat, double lon, CURL *curl);

    //
    // printBusStopInfo
    //
    // given a bus stop, it prints out Information related to that bus stop
    void printBusStopInfo(BusStop &busStop, CURL *curl, double minDistance);

    //
    // getNumBusStops
    //
    // returns the number of bus stops
    int getNumBusStops();
};