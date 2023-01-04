//
// Created by manue on 29/12/2022.
//

#include "Airport.h"
#include <iostream>

using namespace std;

/**
 *
 * @param code
 */
Airport::Airport(const string &code) : code(code) {}

/**
 *
 * @param code
 * @param name
 * @param city
 * @param latitude
 * @param longitude
 * @param number
 */
Airport::Airport(const string &code, const string &name, const City &city, double latitude, double longitude, int number) : code(code), name(name), city(city), latitude(latitude), longitude(longitude), number(number) {}

/**
 *
 * @return
 */
const string &Airport::getCode() const {
    return code;
}
/**
 *
 * @return
 */
const City &Airport::getCity() const {
    return city;
}

/**
 *
 * @return
 */
double Airport::getLatitude() const {
    return latitude;
}

/**
 *
 * @return
 */
double Airport::getLongitude() const {
    return longitude;
}

/**
 *
 * @return
 */
int Airport::getNumber() const {
    return number;
}

/**
 *
 * @param rhs
 * @return
 */
bool Airport::operator==(const Airport &rhs) const {
    return code == rhs.code;
}

/**
 *
 */
void Airport::print() const {
    cout << "Aeroporto " << name << " (" << code << ") - ";
    city.print();
    cout << " (" << latitude << ", " << longitude << ")";
}
