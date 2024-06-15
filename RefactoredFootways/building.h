/*building.h*/

//
// A building in the Open Street Map.
//

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "node.h"
#include "nodes.h"
#include "footways.h"
#include "footway.h"

using namespace std;

//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
//
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Building
{
public:
  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

  //
  // constructor
  //
  Building(long long id, string name, string streetAddr);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

  //
  // print
  //
  // prints a buildings id, name, street address, and nodes
  //
  void print(const Nodes &nodes, const Footways &footways) const;
};
