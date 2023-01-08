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
    void print() const;

private:
    std::string city;
    std::string country;
};

struct cityHash {
    /**Função de dispersão para a tabela de dispersão de cities.
     * <br>Complexidade Temporal: O(n), sendo n a soma dos comprimentos do nome e do país
     * @param city cidade a mapear
     * @return valor da hash para a cidade a mapear
     */
    int operator()(const City &city) const {
        const std::string& str = city.getCity() + city.getCountry();
        int v = 0;
        for (const char &ch : str)
            v = 37*v + ch;
        return v;
    }

    /**Função de igualdade para a tabela de dispersão de cities.
     * <br>Complexidade Temporal: O(n), sendo n o maior comprimento entre o nome e o país das cidades
     * @param city1 cidade 1
     * @param city2 cidade 2
     * @return true se as cidades são iguais, false caso contrário
     */
    bool operator()(const City &city1, const City &city2) const {
        return city1 == city2;
    }
};

#endif //AIRPLANES_CITY_H
