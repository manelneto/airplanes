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
    /**Função de dispersão para a tabela de dispersão de airlines.
     * <br>Complexidade Temporal: O(n), sendo n o comprimento do código ICAO
     * @param airline companhia aérea a mapear
     * @return valor da hash para a companhia aérea a mapear
     */
    int operator()(const Airline &airline) const {
        const std::string& str = airline.getCode();
        int v = 0;
        for (const char &ch : str)
            v = 37*v + ch;
        return v;
    }

    /**Função de igualdade para a tabela de dispersão de airlines.
     * <br>Complexidade Temporal: O(n), sendo n sendo n o maior comprimento entre os códigos ICAO
     * @param airline1 companhia aérea 1
     * @param airline2 companhia aérea 2
     * @return true se as companhias aéreas são iguais, false caso contrário
     */
    bool operator()(const Airline &airline1, const Airline &airline2) const {
        return airline1 == airline2;
    }
};

#endif //AIRPLANES_AIRLINE_H
