//
// Created by manue on 30/12/2022.
//

#include "City.h"
#include <iostream>

using namespace std;

/**
 *
 */
City::City() {}

/**
 *
 * @param city
 * @param country
 */
City::City(const std::string &city, const std::string &country) : city(city), country(country) {}

/**
 *
 * @return
 */
const std::string &City::getCity() const {
    return city;
}

/**
 *
 * @return
 */
const std::string &City::getCountry() const {
    return country;
}

/**
 *
 * @param rhs
 * @return
 */
bool City::operator==(const City &rhs) const {
    return city == rhs.city && country == rhs.country;
}

/**
 *
 */
void City::print() const {
    cout << city << ", " << country;
}
