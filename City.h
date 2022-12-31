//
// Created by manue on 30/12/2022.
//

#ifndef AIRPLANES_CITY_H
#define AIRPLANES_CITY_H


#include <string>

class City {
public:
    City();
    City(const std::string &city, const std::string &country);
    const std::string &getCity() const;
    const std::string &getCountry() const;

    bool operator==(const City &rhs) const;

private:
    std::string city;
    std::string country;
};

struct cityHash {
    int operator()(const City &city) const {
        const std::string& s = city.getCity();
        int v = 0;
        for (char i : s)
            v = 37*v + i;
        return v;
    }

    bool operator()(const City &city1, const City &city2) const {
        return city1 == city2;
    }
};

#endif //AIRPLANES_CITY_H
