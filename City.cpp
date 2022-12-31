//
// Created by manue on 30/12/2022.
//

#include "City.h"
#include <iostream>

using namespace std;

City::City() {}

City::City(const std::string &city, const std::string &country) : city(city), country(country) {}

const std::string &City::getCity() const {
    return city;
}

const std::string &City::getCountry() const {
    return country;
}

bool City::operator==(const City &rhs) const {
    return toUpper(city) == toUpper(rhs.city) && toUpper(country) == toUpper(rhs.country);
}

void City::print() const {
    cout << city << ", " << country;
}

std::string City::toUpper(string str) {
    for (char &ch : str)
        ch = toupper(ch);
    return str;
}
