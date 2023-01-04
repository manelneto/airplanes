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
    void print() const;

private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
};

struct airlineHash {
    int operator()(const Airline &airline) const {
        const std::string& str = airline.getCode();
        int v = 0;
        for (const char &ch : str)
            v = 37*v + ch;
        return v;
    }

    bool operator()(const Airline &airline1, const Airline &airline2) const {
        return airline1 == airline2;
    }
};

#endif //AIRPLANES_AIRLINE_H
