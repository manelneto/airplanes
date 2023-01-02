//
// Created by manue on 29/12/2022.
//

#ifndef AIRPLANES_AIRPORT_H
#define AIRPLANES_AIRPORT_H


#include "City.h"

class Airport {
public:
    Airport(const std::string &code);
    Airport(const std::string &code, const std::string &name, const City &city,
            double latitude, double longitude, int number);
    const std::string &getCode() const;
    const City &getCity() const;
    double getLatitude() const;
    double getLongitude() const;
    int getNumber() const;
    bool operator==(const Airport &rhs) const;
    void print() const;

private:
    std::string code;
    std::string name;
    City city;
    double latitude;
    double longitude;
    int number;
};

struct airportHash {
    int operator()(const Airport &airport) const {
        const std::string& s = airport.getCode();
        int v = 0;
        for (const char &i : s)
            v = 37*v + i;
        return v;
    }

    bool operator()(const Airport &airport1, const Airport &airport2) const {
        return airport1 == airport2;
    }
};

#endif //AIRPLANES_AIRPORT_H
