// << Jay Kiptoo Yegon>>
// << Northwestern University>>
// << Computer Science and Engineering Major>>

#include <iostream>
#include <string>

#include "building.h"
#include "buildings.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//
// findBuilding
//
// Searches through the buldings vector for the one that matches or includes the input name by user.
// If found => Outputs the name, address, bulding ID, and NodeIDs including the latitude, longitude, and presence of entrance of each Node ID.
//
void findBuilding(const vector<Building> &buildings, const string name, const Nodes &nodes)
{
    bool found = false;                        // assume not found
    for (const Building &building : buildings) // for each building
    {
        if (building.Name.find(name) != string::npos) // if the name is in the building name
        {
            cout << building.Name << endl;                         // print the building name
            cout << "Address: " << building.StreetAddress << endl; // print the street address
            cout << "Building ID: " << building.ID << endl;        // print the building ID
            cout << "Nodes:" << endl;                              // print the node IDs
            for (const auto &node : building.NodeIDs)              // for each node in the NODEIDs vector
            {
                // Node nodes;
                double lat, lon;                            // initialize latitude and longitude of the node
                bool isEntrance;                            // boolean for if the node is an entrance node
                if (nodes.find(node, lat, lon, isEntrance)) // if the node exists
                {
                    cout << "  " << node << ": (" << lat << ", " << lon << ")" << (isEntrance ? ", is entrance" : "") << endl; // print the node ID and coordinates
                }
                else
                {                                                      // does not exist
                    cout << "  " << node << "** NOT FOUND **" << endl; // print node, and mark it as not found
                }
            }
        }
    }
}

int main()
{
    string filename; // input file name
    XMLDocument doc; // XML document

    cout << "Enter OSM filename: " << endl;
    getline(cin, filename); // get filename from user

    bool success = osmLoadMapFile(filename, doc); // load OSM file

    if (!success) // if failed to load file
    {
        cout << "Failed to load OSM file" << endl; // output error message and exit
        return 0;
    }
    // declare a Nodes object
    Nodes nodes;
    nodes.readMapNodes(doc);                                  // read the nodes from the XML file
    cout << "# of nodes: " << nodes.getNumMapNodes() << endl; // print the number of nodes

    // declare a Buildings object
    Buildings buildings;
    buildings.readMapBuildings(doc);                                      // read the buildings from the XML file
    cout << "# of buildings: " << buildings.getNumMapBuildings() << endl; // print the number of buildings

    bool proceed = true; // initialize a boolean variable for while loop
    while (proceed)      // while true
    {
        string userInput; // string input from user

        cout << "Enter building name (partial or complete), or * to list, or $ to end: " << endl; // prompt user for input

        getline(cin, userInput); // get input from user

        if (userInput == "$") // if the user enters $
        {
            proceed = false; // set the boolean variable to false and exit the while loop
        }
        else if (userInput == "*") // if the user enters *, meaning list all buildings
        {
            for (const Building &building : buildings.MapBuildings)
            {
                cout << building.ID << ": " << building.Name << ", " << building.StreetAddress << endl; // print the building, name, and street address
            }
        }
        else
        {
            findBuilding(buildings.MapBuildings, userInput, nodes); // find the building with the given name
        }
    }

    cout << endl;
    cout << "** Done **" << endl;

    cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl; // print the number of calls to getID()
    cout << "# of Nodes created: " << Node::getCreated() << endl;         // print the number of Nodes created
    cout << "# of Nodes copied: " << Node::getCopied() << endl;           // print the number of Nodes copied
    return 0;
}
