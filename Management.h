//
// Created by manue on 29/12/2022.
//

#ifndef AIRPLANES_MANAGEMENT_H
#define AIRPLANES_MANAGEMENT_H


#include <unordered_set>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

struct airportHash {
    int operator()(const Airport &airport) const {
        std::string str = airport.getCode();
        int v = 0;
        for (unsigned int i = 0; i < str.size(); i++)
            v = 37*v + str[i];
        return v;
    }

    bool operator()(const Airport &airport1, const Airport &airport2) const {
        return airport1 == airport2;
    }
};

struct airlineHash {
    int operator()(const Airline &airline) const {
        std::string str = airline.getCode();
        int v = 0;
        for (unsigned int i = 0; i < str.size(); i++)
            v = 37*v + str[i];
        return v;
    }

    bool operator()(const Airline &airline1, const Airline &airline2) const {
        return airline1 == airline2;
    }
};

class Management {
public:
    Management();

private:
    std::unordered_set<Airport, airportHash, airportHash> airports;
    std::unordered_set<Airline, airlineHash, airlineHash> airlines;
    Graph flights;
    void readAirportsFile();
    void readAirlinesFile();
    void readFlightsFile();
};


#endif //AIRPLANES_MANAGEMENT_H
