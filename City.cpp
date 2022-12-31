//
// Created by manue on 30/12/2022.
//

#include "City.h"

City::City() {}

City::City(const std::string &city, const std::string &country) : city(city), country(country) {}

const std::string &City::getCity() const {
    return city;
}

const std::string &City::getCountry() const {
    return country;
}

bool City::operator==(const City &rhs) const {
    return city == rhs.city &&
           country == rhs.country;
}
