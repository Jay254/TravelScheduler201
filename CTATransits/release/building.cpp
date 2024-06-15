/*building.cpp*/

//
// A building in the Open Street Map.
//

#include <iostream>

#include "building.h"
#include <utility>

using namespace std;

//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
    : ID(id), Name(name), StreetAddress(streetAddr)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  // this->ID = id;
  // this->Name = name;
  // this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// print
//
// prints information about a building --- id, name, etc. -- to
// the console. The function is passed the Nodes for searching
// purposes.
//
void Building::print(Nodes &nodes, BusStops &busstops, CURL *curl)
{
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;

  cout << "# perimeter nodes: " << this->NodeIDs.size() << endl;
  auto location = this->getLocation(nodes);
  cout << "Location: (" << location.first << ", " << location.second << ")" << endl;
  // cout << location.first << endl;
  //  double lat = this->getLocation(nodes).first;
  //  double lon = this->getLocation(nodes).second;
  busstops.closestStops(location.first, location.second, curl);

  // cout << "Nodes:" << endl;
  // for (long long nodeid : this->NodeIDs)
  // {
  //   cout << "  " << nodeid << ": ";

  //   double lat = 0.0;
  //   double lon = 0.0;
  //   bool entrance = false;

  //   bool found = nodes.find(nodeid, lat, lon, entrance);

  //   if (found) {
  //     cout << "(" << lat << ", " << lon << ")";

  //     if (entrance)
  //       cout << ", is entrance";

  //     cout << endl;
  //   }
  //   else {
  //     cout << "**NOT FOUND**" << endl;
  //   }
  // }//for
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}

//
// gets the center (lat, lon) of the building based
// on the nodes that form the perimeter
//
pair<double, double> Building::getLocation(const Nodes &nodes)
{
  // initialize variables to store avg latitude and longitude
  double avgLat = 0.0;
  double avgLon = 0.0;

  int count = 0; // counter for number of nodes

  for (long long nodeid : this->NodeIDs) // iterate through each node
  {
    // initialize variables to store latitude, longtitude and entrance info
    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance); // search nodeid in given Nodes collection

    if (found) // update avg lat and lon
    {
      avgLat += lat;
      avgLon += lon;
      count++;
    }
  }
  // average them
  avgLat = avgLat / count;
  avgLon = avgLon / count;

  return make_pair(avgLat, avgLon); // return them as a pair
}
