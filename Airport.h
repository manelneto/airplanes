//
// Created by manue on 29/12/2022.
//

#ifndef AIRPLANES_AIRPORT_H
#define AIRPLANES_AIRPORT_H


#include "City.h"

class Airport {
public:
    Airport(const std::string &code);
    Airport(const std::string &code, const std::string &name, const City &city,
            double latitude, double longitude, int number);
    const std::string &getCode() const;
    const City &getCity() const;
    double getLatitude() const;
    double getLongitude() const;
    int getNumber() const;
    bool operator==(const Airport &rhs) const;
    void print() const;

private:
    std::string code;
    std::string name;
    City city;
    double latitude;
    double longitude;
    int number;
};

struct airportHash {
    /**Função de dispersão para a tabela de dispersão de airports.
     * <br>Complexidade Temporal: O(n), sendo n o comprimento do código IATA
     * @param airport aeroporto a mapear
     * @return valor da hash para o aeroporto a mapear
     */
    int operator()(const Airport &airport) const {
        const std::string& str = airport.getCode();
        int v = 0;
        for (const char &ch : str)
            v = 37*v + ch;
        return v;
    }

    /**Função de igualdade para a tabela de dispersão de airports.
     * <br>Complexidade Temporal: O(n), sendo n sendo n o maior comprimento entre os códigos IATA
     * @param airport1 aeroporto 1
     * @param airport2 aeroporto 1
     * @return true se os aeroportos são iguais, false caso contrário
     */
    bool operator()(const Airport &airport1, const Airport &airport2) const {
        return airport1 == airport2;
    }
};

#endif //AIRPLANES_AIRPORT_H
