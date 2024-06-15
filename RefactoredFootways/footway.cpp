/*footway.h*/

// a footway in the Open Street Map.

// <<JAY KIPTOO YEGON>>
// <<COMPUTER SCIENCE AND ENGINEERING MAJOR>>

#include "footway.h"

using namespace std;

// Constructor for the Footway class
Footway::Footway(long long id)
    : ID(id)
{
}

//
// commonFootway
//
// finds common ids between building and footway
void Footway::commonFootway(long long nodeid, vector<long long> &comFootways) const
{
    // iterate through the NodeIDs of the footway
    for (long long footid : this->NodeIDs)
    {
        // Check if the current footway node ID matches the given building node ID
        if (nodeid == footid)
        {
            // If there is a match, add the Footway ID to the comfootways vector
            comFootways.emplace_back(this->ID);
            break;
        }
    }
}