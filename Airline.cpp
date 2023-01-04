//
// Created by manue on 29/12/2022.
//

#include "Airline.h"
#include <iostream>

using namespace std;

/**
 *
 * @param code
 */
Airline::Airline(const std::string &code) : code(code) {}

/**
 *
 * @param code
 * @param name
 * @param callsign
 * @param country
 */
Airline::Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country) : code(code), name(name), callsign(callsign), country(country) {}

/**
 *
 * @return
 */
const std::string &Airline::getCode() const {
    return code;
}

/**
 *
 * @param rhs
 * @return
 */
bool Airline::operator==(const Airline &rhs) const {
    return code == rhs.code;
}

/**
 *
 */
void Airline::print() const {
    cout << name << " (" << code << ") - " << country;
}
