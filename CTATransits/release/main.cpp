/*main.cpp*/

//
// Program to input Nodes (positions) and Buildings from
// an Open Street Map file.
//

// <<JAY KIPTOO YEGON>>
// <<CS 211>>
//<<COMPUTER SCIENCE AND ENGINEERING MAJOR>>

#include <iostream>
#include <string>

#include "building.h"
#include "buildings.h"
#include "busstop.h"
#include "busstops.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "curl_util.h"

using namespace std;
using namespace tinyxml2;

//
// main
//
int main()
{
  XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;

  // initialize CURL for making web requests
  CURL *curl = curl_easy_init();
  if (curl == nullptr) // display error if fail to initialize CURL
  {
    cout << "**ERROR:" << endl;
    cout << "**ERROR: unable to initialize curl library" << endl;
    cout << "**ERROR:" << endl;
    return 0;
  }

  cout << "** NU open street map **" << endl;

  string filename;

  cout << endl;
  cout << "Enter map filename> " << endl; // prompt for map filename
  getline(cin, filename);

  //
  // 1. load XML-based map file
  //
  if (!osmLoadMapFile(filename, xmldoc))
  {
    // failed, error message already output
    return 0;
  }

  //
  // 2. read the nodes, which are the various known positions on the map:
  //
  nodes.readMapNodes(xmldoc);

  //
  // 3. read the university buildings:
  //
  buildings.readMapBuildings(xmldoc);

  // initialize BusStops with busstops data from input file
  BusStops busstops("bus-stops.txt");
  //
  //
  // 4. stats
  //
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout << "# of bus stops: " << busstops.getNumBusStops() << endl;

  //
  // 5. display the map
  //

  //
  // 5. now let the user for search for 1 or more buildings:
  //
  while (true)
  {
    string name;

    cout << endl;
    cout << "Enter building name (partial or complete), or * to list, or @ for bus stops, or $ to end> " << endl; // prompt for input

    getline(cin, name);

    if (name == "$") // exit
    {
      break;
    }
    else if (name == "*") // all buildings
    {
      buildings.print();
    }
    else if (name == "@") // all bus stops
    {
      busstops.printAllBusStops();
    }
    else
    {
      buildings.findAndPrint(name, nodes, busstops, curl); // find building and print data related to it
    }

  } // while

  //
  // done:
  //
  curl_easy_cleanup(curl); // cleanup and display completion message

  cout << endl;
  cout << "** Done **" << endl;

  return 0;
}
