//
// Created by manue on 30/12/2022.
//

#include "City.h"
#include <iostream>

using namespace std;

/**Construtor sem parâmetros. Constrói uma cidade de nome vazio e país vazio.
 * Complexidade Temporal: O(1)
 */
City::City() {}

/**Construtor com parâmetros. Constrói uma cidade de nome city e país country.
 * Complexidade Temporal: O(1)
 * @param city nome
 * @param country país
 */
City::City(const std::string &city, const std::string &country) : city(city), country(country) {}

/**Retorna o nome da cidade.
 * Complexidade Temporal: O(1)
 * @return nome da cidade
 */
const std::string &City::getCity() const {
    return city;
}

/**Retorna o país da cidade.
 * Complexidade Temporal: O(1)
 * @return país da cidade
 */
const std::string &City::getCountry() const {
    return country;
}

/**Compara a cidade e rhs quanto ao nome e ao país.
 * Complexidade Temporal: O(n), sendo n o maior tamanho entre o nome e o país da cidade e de rhs
 * @param rhs cidade com a qual comparar
 * @return true se a cidade e rhs têm igual nome e país, false caso contrário
 */
bool City::operator==(const City &rhs) const {
    return city == rhs.city && country == rhs.country;
}

/**Imprime o nome e o país da cidade.
 * Complexidade Temporal: O(1)
 */
void City::print() const {
    cout << city << ", " << country;
}
