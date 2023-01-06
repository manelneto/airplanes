//
// Created by manue on 29/12/2022.
//

#include "Airline.h"
#include <iostream>

using namespace std;

/**Construtor com parâmetro. Constrói uma companhia aérea com código ICAO code, nome vazio, alcunha vazia e país vazio.
 * Complexidade Temporal: O(1)
 * @param code código ICAO
 */
Airline::Airline(const std::string &code) : code(code) {}

/**Construtor com parâmetros. Constrói uma companhia aérea com código ICAO code, nome name, alcunha callsign e país country.
 * Complexidade Temporal: O(1)
 * @param code código ICAO
 * @param name nome
 * @param callsign alcunha
 * @param country país
 */
Airline::Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country) : code(code), name(name), callsign(callsign), country(country) {}

/**Retorna o código ICAO da companhia aérea.
 * Complexidade Temporal: O(1)
 * @return código ICAO da companhia aérea
 */
const std::string &Airline::getCode() const {
    return code;
}

/**Compara a companhia aérea e rhs quanto ao código ICAO.
 * Complexidade Temporal: O(n), sendo n o maior tamanho entre os códigos ICAO
 * @param rhs companhia aérea com a qual comparar
 * @return true se a companhia áerea e rhs têm igual código ICAO, false caso contrário
 */
bool Airline::operator==(const Airline &rhs) const {
    return code == rhs.code;
}

/**Imprime o nome, o código ICAO e o país da companhia aérea.
 * Complexidade Temporal: O(1)
 */
void Airline::print() const {
    cout << name << " (" << code << ") - " << country;
}
