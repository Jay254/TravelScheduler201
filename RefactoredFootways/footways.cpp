/*footways.cpp*/

// footways in the Open Street Map.

// <<JAY KIPTOO YEGON>>
// <<COMPUTER SCIENCE AND ENGINEERING MAJOR>>

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

#include "footways.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

void Footways::readMapFootways(XMLDocument &doc)
{
    XMLElement *osm = doc.FirstChildElement("osm");
    assert(osm != nullptr);

    //
    // Parse the XML document way by way, looking for university buildings:
    //
    XMLElement *way = osm->FirstChildElement("way");

    while (way != nullptr)
    {
        const XMLAttribute *attr = way->FindAttribute("id");
        assert(attr != nullptr);

        //
        // if this is a building, store info into vector:
        //
        if (osmContainsKeyValue(way, "highway", "footway") ||
            osmContainsKeyValue(way, "area:highway", "footway"))
        {
            string name = osmGetKeyValue(way, "name");

            string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " + osmGetKeyValue(way, "addr:street");

            //
            // create building object, then add the associated
            // node ids to the object:
            //
            long long id = attr->Int64Value();

            Footway F(id);

            XMLElement *nd = way->FirstChildElement("nd");

            while (nd != nullptr)
            {
                const XMLAttribute *ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);

                long long id = ndref->Int64Value();

                F.NodeIDs.push_back(id);

                // advance to next node ref:
                nd = nd->NextSiblingElement("nd");
            }

            //
            // add the building to the vector:
            //
            this->MapFootways.push_back(F);
        } // if

        way = way->NextSiblingElement("way");
    } // while

    //
    // done:
    //
}

//
// getNumMapFootways
//
// returns number of footways in the map
int Footways::getNumMapFootways()
{
    return this->MapFootways.size();
}

//
// commonFootways
//
// Given a node id, checks to see if there are footways that have common ids with the given node id
void Footways::commonFootways(long long nodeid) const
{
    // iterate through each Footway in the MapFootways vector
    for (const Footway &footway : this->MapFootways)
    {
        footway.commonFootway(nodeid, this->comFootways);
    }
    sort(this->comFootways.begin(), this->comFootways.end());                                                     // sort comfootways vector
    this->comFootways.erase(unique(this->comFootways.begin(), this->comFootways.end()), this->comFootways.end()); // erase duplicates
}

//
// getNumCommonFootways
//
// returns number of footways that have common ids with the given node i
int Footways::getNumCommonFootways() const
{
    return this->comFootways.size(); // get size of comFootways vector
}