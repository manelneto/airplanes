//
// Created by manue on 29/12/2022.
//

#ifndef AIRPLANES_MANAGEMENT_H
#define AIRPLANES_MANAGEMENT_H


#include <unordered_set>
#include <set>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

class Management {
public:
    Management();
    int menu();
private:
    std::unordered_set<Airport, airportHash, airportHash> airports;
    std::unordered_set<Airline, airlineHash, airlineHash> airlines;
    std::unordered_set<City, cityHash, cityHash> cities;
    Graph flights = Graph(0);
    void readAirportsFile();
    void readAirlinesFile();
    void readFlightsFile();
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    static bool isInt(const std::string &str);
    static bool isDouble(const std::string &str);
    static void toUpper(std::string &str);
    static std::string readString();
    static int readInt();
    static double readDouble();
    static int validateOption(int option, int min, int max);
    Airport readAirport() const;
    Airline readAirline() const;
    City readCity() const;
    std::pair<double, double> readLocation();
    std::list<Airport> getAirports(const City &city);
    std::list<Airport> getAirports(double latitude, double longitude, double range);
    static std::unordered_set<int> getNumbers(const std::list<Airport> &airports);
    std::list<Airport> lerLocal();
    void melhorVoo();
    void imprimirVoo(const std::vector<int> &path, const std::unordered_set<std::string> &desiredAirlinesCodes);
    void informacoes();
};


#endif //AIRPLANES_MANAGEMENT_H
