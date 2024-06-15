/*footway.h*/

// a footway in the Open Street Map.

// <<JAY KIPTOO YEGON>>
// <<COMPUTER SCIENCE AND ENGINEERING MAJOR>>

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "node.h"
#include "nodes.h"

using namespace std;

class Footway
{
public:
    long long ID;              // footway id
    vector<long long> NodeIDs; // footway's vector of node ids

    //
    // Constructor
    //
    Footway(long long ID);

    //
    // commonFootway
    //
    // finds common ids between building and footway
    void commonFootway(long long nodeid, vector<long long> &comFootways) const;
};