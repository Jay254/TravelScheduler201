/*buildings.cpp*/

// Contains fuction definition to read buildings from an osm file, and push it into a bulding vector - ReadMapBuildings()
// Also a fuction that gets the number of buildings in the bulding vector - GetNumMapBuldings()

// << Jay Kiptoo Yegon>>
// << Northwestern University>>
// << Computer Science and Engineering Major>>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include "buildings.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//
// readMapBuildings
//
// reads the buildings from an osm file and pushes them into a bulding vector
//

void Buildings::readMapBuildings(XMLDocument &xmldoc)
{
    XMLElement *osm = xmldoc.FirstChildElement("osm"); // get the osm element
    assert(osm != nullptr);

    XMLElement *way = osm->FirstChildElement("way"); // get the way element

    while (way != nullptr) // while there are ways in the osm file
    {
        if (osmContainsKeyValue(way, "building", "university")) // contains building and university
        {
            const XMLAttribute *idref = way->FindAttribute("id"); // id of the building
            assert(idref != nullptr); // id of the building is not null
            long long id = idref->Int64Value(); // convert to long long
            // cout << id << endl;
            string name = osmGetKeyValue(way, "name"); // name of the building
            // cout << name << endl;
            string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " + osmGetKeyValue(way, "addr:street"); // street address of the building
            // cout << streetAddr << endl;

            Building B(id, name, streetAddr); // create a building object

            XMLElement *nd = way->FirstChildElement("nd"); // get the first node of the building

            while (nd != nullptr) // get all the nodes of the building
            {
                const XMLAttribute *ndref = nd->FindAttribute("ref"); // id of the node
                assert(ndref != nullptr);                             // check if the node has valid id

                long long id = ndref->Int64Value(); // convert to long long

                B.add(id); // add to Bulding's NodeIDs vector

                // advance to next node ref;
                nd = nd->NextSiblingElement("nd");
            }

            this->MapBuildings.push_back(B); // add to buildings vector
        }

        way = way->NextSiblingElement("way"); // advance to next way
    }
}

//
// getNumMapBuildings
//
// returns the number of buildings in the bulding vector
//

int Buildings::getNumMapBuildings() const
{
    return (int)this->MapBuildings.size();
}

// void Buildings::getBuildings(int& i) const
// {
//     cout << this->MapBuildings << endl;
// }