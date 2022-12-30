//
// Created by manue on 29/12/2022.
//

#include "Airline.h"

Airline::Airline(const std::string &code, const std::string &name, const std::string &callsign,
                 const std::string &country) : code(code), name(name), callsign(callsign), country(country) {}

const std::string &Airline::getCode() const {
    return code;
}

const std::string &Airline::getName() const {
    return name;
}

const std::string &Airline::getCallsign() const {
    return callsign;
}

const std::string &Airline::getCountry() const {
    return country;
}

bool Airline::operator==(const Airline &rhs) const {
    return code == rhs.code;
}
