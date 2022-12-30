//
// Created by manue on 29/12/2022.
//

#include "Airport.h"

using namespace std;

Airport::Airport() {}

Airport::Airport(const string &code) : code(code) {}

Airport::Airport(const std::string &code, const std::string &name, const std::string &city, const std::string &country,
                 double latitude, double longitude) : code(code), name(name), city(city), country(country),
                                                      latitude(latitude), longitude(longitude) {}

const string &Airport::getCode() const {
    return code;
}

bool Airport::operator==(const Airport &rhs) const {
    return code == rhs.code;
}
