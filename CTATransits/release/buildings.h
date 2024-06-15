/*buildings.h*/

//
// A collection of buildings in the Open Street Map.
//

// <<JAY KIPTOO YEGON>>
// <<COMPUTER SCIENCE AND ENGINEERING MAJOR>>

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "node.h"
#include "nodes.h"
#include "building.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//
// Keeps track of all the buildings in the map.
//
class Buildings
{
public:
  vector<Building> MapBuildings;

  // map<string, int> SouthBounds;
  // map<string, int> NorthBounds;

  //
  // readMapBuildings
  //
  // Given an XML document, reads through the document and
  // stores all the buildings into the given vector.
  //
  void readMapBuildings(XMLDocument &xmldoc);

  //
  // print
  //
  // prints each building (id, name, address) to the console.
  //
  void print();

  //
  // findAndPrint
  //
  // Prints each building that contains the given name.
  //
  void findAndPrint(string name, Nodes &nodes, BusStops &busstops, CURL *curl);

  //
  // accessors / getters
  //
  int getNumMapBuildings();
};
