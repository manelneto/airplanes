//
// Created by manue on 29/12/2022.
//

#ifndef AIRPLANES_AIRLINE_H
#define AIRPLANES_AIRLINE_H


#include <string>

class Airline {
public:
    Airline(const std::string &code);
    Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country);
    const std::string &getCode() const;
    bool operator==(const Airline &rhs) const;

private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
};


#endif //AIRPLANES_AIRLINE_H
