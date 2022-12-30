//
// Created by manue on 29/12/2022.
//

#ifndef AIRPLANES_MANAGEMENT_H
#define AIRPLANES_MANAGEMENT_H


#include <unordered_set>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

class Management {
public:
    Management();

private:
    std::unordered_set<Airport, airportHash, airportHash> airports;
    std::unordered_set<Airline, airlineHash, airlineHash> airlines;
    Graph flights = Graph(0);
    void readAirportsFile();
    void readAirlinesFile();
    void readFlightsFile();
};


#endif //AIRPLANES_MANAGEMENT_H
