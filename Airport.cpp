//
// Created by manue on 29/12/2022.
//

#include "Airport.h"

using namespace std;

Airport::Airport(const string &code) : code(code) {}

Airport::Airport(const string &code, const string &name, const City &city, double latitude,
                 double longitude, int number) : code(code), name(name), city(city), latitude(latitude),
                                     longitude(longitude), number(number) {}

const string &Airport::getCode() const {
    return code;
}

const string &Airport::getName() const {
    return name;
}

const City &Airport::getCity() const {
    return city;
}

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}

int Airport::getNumber() const {
    return number;
}

bool Airport::operator==(const Airport &rhs) const {
    return code == rhs.code;
}