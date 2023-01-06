//
// Created by manue on 29/12/2022.
//

#include "Airport.h"
#include <iostream>

using namespace std;

/**Construtor com parâmetro. Constrói um aeroporto com código IATA code, nome vazio, cidade vazia, latitude indefinida, longitude indefinida e número indefinido.
 * Complexidade Temporal: O(1)
 * @param code código IATA
 */
Airport::Airport(const string &code) : code(code) {}

/**Construtor com parâmetros. Constrói um aeroporto com código IATA code, nome name, cidade city, latitude latitude, longitude longitude e número number.
 * Complexidade Temporal: O(1)
 * @param code código IATA
 * @param name nome
 * @param city cidade
 * @param latitude latitude
 * @param longitude longitude
 * @param number número
 */
Airport::Airport(const string &code, const string &name, const City &city, double latitude, double longitude, int number) : code(code), name(name), city(city), latitude(latitude), longitude(longitude), number(number) {}

/**Retorna o código IATA do aeroporto.
 * Complexidade Temporal: O(1)
 * @return código IATA do aeroporto
 */
const string &Airport::getCode() const {
    return code;
}
/**Retorna a cidade do aeroporto.
 * Complexidade Temporal: O(1)
 * @return cidade do aeroporto
 */
const City &Airport::getCity() const {
    return city;
}

/**Retorna a latitude do aeroporto.
 * Complexidade Temporal: O(1)
 * @return latitude do aeroporto
 */
double Airport::getLatitude() const {
    return latitude;
}

/**Retorna a longitude do aeroporto.
 * Complexidade Temporal: O(1)
 * @return longitude do aeroporto
 */
double Airport::getLongitude() const {
    return longitude;
}

/**Retorna o número do aeroporto.
 * Complexidade Temporal: O(1)
 * @return número do aeroporto
 */
int Airport::getNumber() const {
    return number;
}

/**Compara o aeroporto e rhs quanto ao código IATA.
 * Complexidade Temporal: O(n), sendo n o maior tamanho entre os códigos IATA
 * @param rhs aeroporto com o qual comparar
 * @return true se o aeroporto e rhs têm igual código IATA, false caso contrário
 */
bool Airport::operator==(const Airport &rhs) const {
    return code == rhs.code;
}

/**Imprime o nome, o código IATA, a cidade, a latitude e a longitude do aeroporto.
 * Complexidade Temporal: O(1)
 */
void Airport::print() const {
    cout << "Aeroporto " << name << " (" << code << ") - ";
    city.print();
    cout << " (" << latitude << ", " << longitude << ")";
}
