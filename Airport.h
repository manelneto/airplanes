//
// Created by manue on 29/12/2022.
//

#ifndef AIRPLANES_AIRPORT_H
#define AIRPLANES_AIRPORT_H


#include <string>

class Airport {
public:
    Airport();
    Airport(const std::string &code);
    Airport(const std::string &code, const std::string &name, const std::string &city, const std::string &country,
            double latitude, double longitude);
    const std::string &getCode() const;
    bool operator==(const Airport &rhs) const;

private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;
};

#endif //AIRPLANES_AIRPORT_H
