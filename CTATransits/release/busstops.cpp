/*busstops.cpp*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <stdexcept>

#include "busstops.h"
#include "json.hpp"
// #include "node.h"
// #include "nodes.h"

using namespace std;
using json = nlohmann::json;

//
// compareById
//
// sorts busstops by id in ascending order
bool compareById(BusStop busstop1, BusStop busstop2)
{
    return busstop1.stopID < busstop2.stopID;
}

//
// Constructor
//

BusStops::BusStops(string filename)
{
    // cout << filename << endl;
    // open and read busstops data file
    ifstream file;
    file.open(filename);
    string line, stopID, busRoute, stopName, travelDirection, stopLocation, lat, lon;

    while (!file.eof())
    {
        getline(file, line);

        if (file.fail())
        {
            break;
        }
        stringstream parser(line);

        // parse each field from the csv file
        getline(parser, stopID, ',');
        getline(parser, busRoute, ',');
        getline(parser, stopName, ',');
        getline(parser, travelDirection, ',');
        getline(parser, stopLocation, ',');
        getline(parser, lat, ',');
        getline(parser, lon, '\n');

        // cout << stopID << busRoute << stopName << travelDirection << stopLocation << lat << lon << endl;

        // create a busstops object and add it to the BusStops vector
        this->Busstops.emplace_back(stoi(stopID), stoi(busRoute), stopName, travelDirection, stopLocation, stod(lat), stod(lon));
    }
    // sort the busstops vector
    sort(this->Busstops.begin(), this->Busstops.end(), compareById);
}

//
// print
//
// prints out all the bus stops
void BusStops::printAllBusStops()
{
    for (auto &stop : Busstops)
    { // print each bus stop with its print method
        // cout << stop.stopID << ": bus " << stop.busRoute << ", " << stop.stopName << ", " << stop.travelDirection << ", " << stop.stopLocation << ", location (" << stop.lat << ", " << stop.lon << ")" << endl;
        stop.print();
    }
}

//
// printBusStopInfo
//
// given a bus stop, it prints out Information related to that bus stop

void BusStops::printBusStopInfo(BusStop &stop, CURL *curl, double minDistance)
{
    cout << "  " << stop.stopID << ": " << stop.stopName << ", bus #" << stop.busRoute << ", " << stop.stopLocation << ", " << minDistance << " miles" << endl;

    // construct the URL for bus predictions using stop information
    auto url = "http://ctabustracker.com/bustime/api/v2/getpredictions?key=buHjzuSEByEJTbRgXLm7qYA6F&rt=" + to_string(stop.busRoute) + "&stpid=" + to_string(stop.stopID) + "&format=json";
    string response;

    // call the web server
    bool success = callWebServer(curl, url, response);

    // cout << success << response << endl;

    if (success) // if call success
    {
        // parse the response
        auto jsondata = json::parse(response);
        auto bus_response = jsondata["bustime-response"];
        auto predictions = bus_response["prd"];

        // auto prd = bus_response.find("prd");
        // cout << prd << endl;

        // if predictions are available and not empty
        if (predictions.is_array() && !predictions.empty())
        {
            for (auto &M : predictions) // loop through each prediction
            {
                try
                {
                    cout << "  vehicle #" << stoi(M["vid"].get_ref<std::string &>()) << " on route " << stoi(M["rt"].get_ref<std::string &>()) << " travelling " << M["rtdir"].get_ref<std::string &>() << " to arrive in " << stoi(M["prdctdn"].get_ref<std::string &>()) << " mins" << endl;
                }
                catch (exception &e) // handle exceptions in parsing
                {
                    cout << "  error" << endl;
                    cout << " malformed CTA response, prediction unavailable"
                         << " (error: " << e.what() << ")" << endl;
                }
            }
        }
        else
        {
            cout << "  <<no predictions available>>" << endl;
        }
    }
    else // web call server fails
    {
        cout << "  <<bus predictions unavailable, call failed>>" << endl;
    }
}

//
// closestStops
//
// finds the closest bus southbound and northbound stops to a given location
void BusStops::closestStops(double lat, double lon, CURL *curl)
{
    // set maximum finite representable value for 'double' data type
    double minDistanceSouth = numeric_limits<double>::max();
    double minDistanceNorth = numeric_limits<double>::max();

    // to store info about closest stops
    BusStop closestStopSouth;
    BusStop closestStopNorth;
    double dist;
    // cout << lat << " " << lon << endl;
    for (auto &busstop : this->Busstops) // iterate through bus stops to find closest northbound and southbound
    {
        // cout<< "building loc: " << lat << " " << lon << endl;
        // cout << "busstop loc: " << busstop.lat << " " << busstop.lon << endl;
        // cout << endl;
        // cout << busstop.lat << " " << busstop.lon << " " << lat << " " << lon << endl;
        dist = distBetween2Points(busstop.lat, busstop.lon, lat, lon);

        // cout << dist << endl;

        if (busstop.travelDirection == "Southbound" && dist < minDistanceSouth) // if stop is southbound
        {
            minDistanceSouth = dist;
            closestStopSouth = busstop;
            // cout << "South: " << dist << endl;
        }
        else if (busstop.travelDirection == "Northbound" && dist < minDistanceNorth) // if stop is northbound
        {
            minDistanceNorth = dist;
            closestStopNorth = busstop;
            // cout << "North: " << dist << endl;
        }
    }
    // print info about closest southbound stop
    cout << "Closest southbound bus stop:" << endl;
    printBusStopInfo(closestStopSouth, curl, minDistanceSouth);

    // print info about closest northbound stop
    cout << "Closest northbound bus stop:" << endl;
    printBusStopInfo(closestStopNorth, curl, minDistanceNorth);

    // cout << "Closest southbound bus stop:" << endl;
    // cout << "  " << closestStopSouth.stopID << ": " << closestStopSouth.stopName << ", bus #" << closestStopSouth.busRoute << ", " << closestStopSouth.stopLocation << ", " << minDistanceSouth << " miles" << endl;

    // auto urlS = "http://ctabustracker.com/bustime/api/v2/getpredictions?key=buHjzuSEByEJTbRgXLm7qYA6F&rt=" + to_string(closestStopSouth.busRoute) + "&stpid=" + to_string(closestStopSouth.stopID) + "&format=json";
    // string response;

    // bool success = callWebServer(curl, urlS, response);

    // //cout << success << response << endl;

    // if (!success)
    // {
    //     cout << "  <<bus predictions unavailable, call failed>>" << endl;
    // }
    // else
    // {
    //     auto jsondata = json::parse(response);
    //     auto bus_response = jsondata["bustime-response"];
    //     auto predictions = bus_response["prd"];

    //     for(auto& M : predictions)
    //     {
    //         try
    //         {
    //             cout << "  vehicle #" << stoi(M["vid"].get_ref<std::string &>()) << " on route " << stoi(M["rt"].get_ref<std::string &>()) << " travelling " << M["rtdir"].get_ref<std::string &>() << " to arrive in " << stoi(M["prdctdn"].get_ref<std::string &>()) << " mins" << endl;
    //         }
    //         catch (exception& e)
    //         {
    //             cout << "  error" << endl;
    //             cout << " malformed CTA response, prediction unavailable" << " (error: " << e.what() << ")" << endl;
    //         }

    //     }
    // }
    // cout << "Closest northbound bus stop:" << endl;
    // cout << "  " << closestStopNorth.stopID << ": " << closestStopNorth.stopName << ", bus #" << closestStopNorth.busRoute << ", " << closestStopNorth.stopLocation << ", " << minDistanceNorth << " miles" << endl;

    // auto urlN = "http://ctabustracker.com/bustime/api/v2/getpredictions?key=buHjzuSEByEJTbRgXLm7qYA6F&rt=" + to_string(closestStopNorth.busRoute) + "&stpid=" + to_string(closestStopNorth.stopID) + "&format=json";
    // string response2;

    // bool success2 = callWebServer(curl, urlN, response2);

    // //cout << success << response << endl;

    // if (!success2)
    // {
    //     cout << "  <<bus predictions unavailable, call failed>>" << endl;
    // }
    // else
    // {
    //     auto jsondata = json::parse(response2);
    //     auto bus_response = jsondata["bustime-response"];
    //     auto predictions = bus_response["prd"];

    //     for(auto& M : predictions)
    //     {
    //         try
    //         {
    //             cout << "  vehicle #" << stoi(M["vid"].get_ref<std::string &>()) << " on route " << stoi(M["rt"].get_ref<std::string &>()) << " travelling " << M["rtdir"].get_ref<std::string &>() << " to arrive in " << stoi(M["prdctdn"].get_ref<std::string &>()) << " mins" << endl;
    //         }
    //         catch (exception& e)
    //         {
    //             cout << "  error" << endl;
    //             cout << " malformed CTA response, prediction unavailable" << " (error: " << e.what() << ")" << endl;
    //         }

    //     }
    // }
}

//
// getNumBusStops
//
// returns the number of bus stops
int BusStops::getNumBusStops()
{
    return this->Busstops.size();
}