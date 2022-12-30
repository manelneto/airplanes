//
// Created by manue on 29/12/2022.
//

#include "Airport.h"

using namespace std;

Airport::Airport(const string &code) : code(code) {}

Airport::Airport(const string &code, const string &name, const string &city, const string &country, double latitude,
                 double longitude, int number) : code(code), name(name), city(city), country(country), latitude(latitude),
                                     longitude(longitude), number(number) {}

const string &Airport::getCode() const {
    return code;
}

const string &Airport::getName() const {
    return name;
}

const string &Airport::getCity() const {
    return city;
}

const string &Airport::getCountry() const {
    return country;
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