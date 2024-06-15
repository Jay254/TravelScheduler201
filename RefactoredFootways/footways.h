/*footways.h*/

// footways in the Open Street Map.

// <<JAY KIPTOO YEGON>>
// <<COMPUTER SCIENCE AND ENGINEERING MAJOR>>

#pragma once

#include <vector>
#include <iostream>
#include "footway.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Footways
{
public:
    vector<Footway> MapFootways;
    mutable vector<long long> comFootways;

    // Footways(long long id);
    //
    //  readMapFootways
    //
    //  Given an XML document, reads through the document and
    //  stores all the footways into the given vector
    void readMapFootways(XMLDocument &doc);

    //
    // getNumMapFootways
    //
    // returns number of footways in the map
    int getNumMapFootways();

    //
    // commonFootways
    //
    // Given a node id, checks to see if there are footways that have common ids with the given node id
    void commonFootways(long long nodeid) const;

    //
    // getNumCommonFootways
    //
    // returns number of footways that have common ids with the given node i
    int getNumCommonFootways() const;
};