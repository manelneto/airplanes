//
// Created by manue on 29/12/2022.
//

#include "Airline.h"

using namespace std;

Airline::Airline(const string &code) : code(code) {}

Airline::Airline(const std::string &code, const std::string &name, const std::string &callsign,
                 const std::string &country) : code(code), name(name), callsign(callsign), country(country) {}

const string &Airline::getCode() const {
    return code;
}

bool Airline::operator==(const Airline &rhs) const {
    return code == rhs.code;
}

