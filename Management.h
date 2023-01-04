//
// Created by manue on 29/12/2022.
//

#ifndef AIRPLANES_MANAGEMENT_H
#define AIRPLANES_MANAGEMENT_H


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
    static std::string toUpper(const std::string &str);
    static std::string readInput();
    static int readInt();
    static double readDouble();
    static int validateInt(int n, int min, int max);
    static double validateDouble(double n, double min, double max);
    Airport readAirport() const;
    Airline readAirline() const;
    City readCity() const;
    std::pair<double, double> readLocation() const;
    std::list<Airport> getAirports(const City &city) const;
    std::list<Airport> getAirports(double latitude, double longitude, double range) const;
    std::list<Airport> getAirports(int y) const;
    static std::unordered_set<int> getNumbers(const std::list<Airport> &airports);
    std::unordered_set<std::string> getAirlinesCodes() const;
    std::list<Airport> lerLocal() const;
    std::unordered_set<std::string> lerRede() const;
    void melhorVoo();
    void imprimirVoo(const std::vector<int> &path, const std::unordered_set<std::string> &desiredAirlinesCodes) const;
    void informacoes();
    void partidas(const Airport &airport) const;
    void companhiasAereas(const Airport &airport) const;
    void destinos(const Airport &airport) const;
    void paises(const Airport &airport) const;
    void yVoos(const Airport &airport);
    void yVoosAeroportos(const Airport &airport, int y) const;
    void yVoosCidades(const Airport &airport, int y) const;
    void yVoosPaises(const Airport &airport, int y) const;
    void pontosArticulacao();
};


#endif //AIRPLANES_MANAGEMENT_H
