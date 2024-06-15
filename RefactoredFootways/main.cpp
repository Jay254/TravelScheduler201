/*main.cpp*/

//
// Program to input Nodes (positions) and Buildings from
// an Open Street Map file.
//

// <<JAY KIPTOO YEGON>>
// <<COMPUTER SCIENCE AND ENGINEERING MAJOR>>

#include <iostream>
#include <string>

#include "building.h"
#include "buildings.h"
#include "footway.h"
#include "footways.h"
// #include "intersect.h"
// #include "intersect.cpp"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

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
  Footways footways;
  // Intersect intersect;

  cout << "** NU open street map **" << endl;

  string filename;

  cout << endl;
  cout << "Enter map filename> " << endl;
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

  //
  // 4. read the footways:
  //
  footways.readMapFootways(xmldoc);

  //
  // 5. stats
  //
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout << "# of footways: " << footways.getNumMapFootways() << endl;

  //
  // 5. now let the user for search for 1 or more buildings:
  //
  while (true)
  {
    string name;

    cout << endl;
    cout << "Enter building name (partial or complete), or * to list, or $ to end> " << endl;

    getline(cin, name); // get user input

    if (name == "$")
    { // $ to terminate program
      break;
    }
    else if (name == "*")
    { // * to list all buildings
      buildings.print();
    }
    else
    {

      //
      // find every building that contains this name:
      //
      buildings.findAndPrint(name, nodes, footways);

    } // else

  } // while

  //
  // done:
  //
  cout << endl;
  cout << "** Done **" << endl;
  cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl; // number of calls to getID()
  cout << "# of Nodes created: " << Node::getCreated() << endl;         // number of Nodes created
  cout << "# of Nodes copied: " << Node::getCopied() << endl;           // number of Nodes copied

  return 0;
}
