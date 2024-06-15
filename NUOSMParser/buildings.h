/*buildings.h*/
//
// A collection of buildings in the Open Street Map.
//
// << Jay Kiptoo Yegon>>
// << Northwestern University>>
// << Computer Science and Engineering Major>>
//

#pragma once

#include <vector>
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

    //
    // readMapBuildings
    //
    // Given an XML document, reads through the document and
    // stores all the buildings into the given vector.
    //
    void readMapBuildings(XMLDocument &xmldoc);

    //
    // accessors / getters
    //
    int getNumMapBuildings() const;

    // void getBuildings(int& i) const;
};