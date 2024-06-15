/*building.cpp*/

//
// A building in the Open Street Map.
//

#include "building.h"

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
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}

//
// print
//
// prints a buildings id, name, street address, and nodes
//
void Building::print(const Nodes &nodes, const Footways &footways) const
{
  // print building information
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;

  cout << "Nodes: " << this->NodeIDs.size() << endl;
  for (long long nodeid : this->NodeIDs) // print node information
  {
    cout << " " << nodeid << ": ";

    double lat = 0.0;      // latitude
    double lon = 0.0;      // longitude
    bool entrance = false; // entrance flag

    bool found = nodes.find(nodeid, lat, lon, entrance); // find node

    if (found) // node found
    {
      cout << "(" << lat << ", " << lon << ")";

      if (entrance) // if its an entrance node
        cout << ", is entrance";

      cout << endl;
    }
    else // node not found
    {
      cout << "**NOT FOUND**" << endl;
    }

    footways.commonFootways(nodeid); //

  } // for

  // # footways that intersect with the building
  cout << "Footways that intersect: " << footways.getNumCommonFootways() << endl;

  if (footways.getNumCommonFootways() > 0) // print footways that intersect
  {
    for (long long footwayid : footways.comFootways)
    {
      cout << " Footway " << footwayid << endl; // print footway information
    }
    footways.comFootways.clear();
  }
  else // no footways that intersect with the building
  {
    cout << " None" << endl;
  }
  // this->NodeIDs
  // footways.NodeIDs
}