//
// Created by manue on 29/12/2022.
//

#include "Management.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

/**
 *
 */
Management::Management() {
    readAirportsFile();
    readAirlinesFile();
    readFlightsFile();
}

/**
 *
 */
void Management::readAirportsFile() {
    ifstream in("../files/airports.csv");
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro airports.csv." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return;
    }
    string line;
    getline(in, line);
    int number = 1;
    while (getline(in, line)) {
        istringstream iss(line);
        string field;
        vector<string> fields(6);
        unsigned f = 0;
        while (getline(iss, field, ','))
            fields[f++] = field;
        string code = fields[0];
        string name = fields[1];
        string cityName = fields[2];
        string country = fields[3];
        double latitude = stod(fields[4]);
        double longitude = stod(fields[5]);
        City city = City(cityName, country);
        Airport airport = Airport(code, name, city, latitude, longitude, number++);
        cities.insert(city);
        airports.insert(airport);
        flights.addNode(code);
    }
    cout << "Leitura de ficheiro airports.csv bem-sucedida." << endl;
}

/**
 *
 */
void Management::readAirlinesFile() {
    ifstream in("../files/airlines.csv");
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro airlines.csv." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return;
    }
    string line;
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        string field;
        vector<string> fields(4);
        unsigned f = 0;
        while (getline(iss, field, ','))
            fields[f++] = field;
        string code = fields[0];
        string name = fields[1];
        string callsign = fields[2];
        string country = fields[3];
        Airline airline = Airline(code, name, callsign, country);
        airlines.insert(airline);
    }
    cout << "Leitura de ficheiro airlines.csv bem-sucedida." << endl;
}

/**
 *
 */
void Management::readFlightsFile() {
    ifstream in("../files/flights.csv");
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro flights.csv." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return;
    }
    string line;
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        string field;
        vector<string> fields(3);
        unsigned f = 0;
        while (getline(iss, field, ','))
            fields[f++] = field;
        auto source = airports.find(Airport(fields[0]));
        auto target = airports.find(Airport(fields[1]));
        flights.addEdge(source->getNumber(), target->getNumber(), fields[2]);
    }
    cout << "Leitura de ficheiro flights.csv bem-sucedida." << endl;
}

/**
 *
 * @param lat1
 * @param lon1
 * @param lat2
 * @param lon2
 * @return
 */
double Management::haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

/**
 *
 * @param str
 * @return
 */
bool Management::isInt(const string &str) {
    for (const char &ch : str)
        if (!isdigit(ch))
            return false;
    return true;
}

/**
 *
 * @param str
 * @return
 */
bool Management::isDouble(const string &str) {
    int points = 0;
    for (unsigned i = 0; i < str.length(); i++) {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '.')
            return false;
        if (str[i] == '.')
            points++;
        if (points > 1 || (str[i] == '-' && i != 0) || (str[i] == '.' && i == 0))
            return false;
    }
    return true;
}

/**
 *
 * @param str
 * @return
 */
string Management::toUpper(const string &str) {
    string upper;
    for (const char &ch : str)
        upper += (char) toupper(ch);
    return upper;
}

/**
 *
 * @return
 */
string Management::readInput() {
    string s;
    getline(cin, s);
    cout << endl;
    return s;
}

/**
 *
 * @return
 */
int Management::readInt() {
    string s = readInput();
    while (!isInt(s)) {
        cout << "Deve inserir um número inteiro não negativo. Tente novamente: ";
        s = readInput();
    }
    int n = stoi(s);
    return n;
}

/**
 *
 * @return
 */
double Management::readDouble() {
    string s = readInput();
    while (!isDouble(s)) {
        cout << "Deve inserir um número e o separador de casas decimais deve ser o ponto (.). Tente novamente: ";
        s = readInput();
    }
    double n = stod(s);
    return n;
}

/**
 *
 * @param n
 * @param min
 * @param max
 * @return
 */
int Management::validateInt(int n, int min, int max) {
    while (n < min || n > max) {
        cout << "O número inserido não é válido (deve pertencer ao intervalo [" << min << ", " << max << "]). Tente novamente: ";
        n = readInt();
    }
    return n;
}

/**
 *
 * @param n
 * @param min
 * @param max
 * @return
 */
double Management::validateDouble(double n, double min, double max) {
    while (n < min || n > max) {
        cout << "O número inserido não é válido (deve pertencer ao intervalo [" << min << ", " << max << "]). Tente novamente: ";
        n = readDouble();
    }
    return n;
}

/**
 *
 * @return
 */
Airport Management::readAirport() const {
    cout << "Código IATA do Aeroporto: ";
    string code = readInput();
    Airport airport = Airport(toUpper(code));
    while (airports.find(airport) == airports.end()) {
        cout << "Aeroporto não encontrado. Tente novamente." << endl;
        airport = readAirport();
    }
    return *airports.find(airport);
}

/**
 *
 * @return
 */
Airline Management::readAirline() const {
    cout << "Código ICAO da Companhia Aérea: ";
    string code = readInput();
    Airline airline = Airline(toUpper(code));
    while (airlines.find(airline) == airlines.end()) {
        cout << "Companhia Aérea não encontrada. Tente novamente." << endl;
        airline = readAirline();
    }
    return *airlines.find(airline);
}

/**
 *
 * @return
 */
City Management::readCity() const {
    cout << "Cidade: ";
    string cityName = readInput();
    cout << "País: ";
    string country = readInput();
    City city(cityName, country);
    while (cities.find(city) == cities.end()) {
        cout << "Cidade não encontrada. Tente novamente." << endl;
        city = readCity();
    }
    return *cities.find(city);
}

/**
 *
 * @return
 */
pair<double, double> Management::readLocation() const {
    cout << "Latitude: ";
    double lat = readDouble();
    lat = validateDouble(lat, -90.0, 90.0);
    cout << "Longitude: ";
    double lon = readDouble();
    lon = validateDouble(lon, -180.0, 180.0);
    return make_pair(lat, lon);
}

/**
 *
 * @param city
 * @return
 */
list<Airport> Management::getAirports(const City &city) const {
    list<Airport> res;
    for (const Airport &airport: airports)
        if (airport.getCity() == city)
            res.push_back(airport);
    return res;
}

/**
 *
 * @param latitude
 * @param longitude
 * @param range
 * @return
 */
list<Airport> Management::getAirports(const double latitude, const double longitude, const double range) const {
    list<Airport> res;
    for (const Airport &airport: airports)
        if (haversine(latitude, longitude, airport.getLatitude(), airport.getLongitude()) < range)
            res.push_back(airport);
    return res;
}

/**
 *
 * @param y
 * @return
 */
list<Airport> Management::getAirports(const int y) const {
    list<Airport> res;
    for (const Node &node : flights.getNodes())
        if (node.distance <= y && node.distance > 0)
            res.push_back(*airports.find(Airport(node.airportCode)));
    return res;
}

/**
 *
 * @param airports
 * @return
 */
unordered_set<int> Management::getNumbers(const list<Airport> &airports) {
    unordered_set<int> numbers;
    for (const Airport &airport : airports)
        numbers.insert(airport.getNumber());
    return numbers;
}

/**
 *
 * @return
 */
unordered_set<string> Management::getAirlinesCodes() const {
    unordered_set<string> airlinesCodes;
    for (const Airline &airline : airlines)
        airlinesCodes.insert(airline.getCode());
    return airlinesCodes;
}

/**
 *
 * @return
 */
int Management::menu() {
    cout << "\nMenu Principal:\n1 - Melhor maneira de voar entre dois locais\n2 - Informações sobre um aeroporto\n3 - Calcular os pontos de articulação existentes na rede\n0 - Sair\nOpção: ";
    int option = readInt();
    option = validateInt(option, 0, 3);
    if (option == 1)
        melhorVoo();
    else if (option == 2)
        informacoes();
    else if (option == 3)
        pontosArticulacao();
    else
        return 0;
    return 1;
}

/**
 *
 * @return
 */
list<Airport> Management::lerLocal() const {
    cout << "\nLocal:\n1 - Aeroporto\n2 - Cidade\n3 - Localização\nOpção: ";
    int option = readInt();
    option = validateInt(option, 1, 3);
    list<Airport> res;
    if (option == 1)
        res.push_back(readAirport());
    else if (option == 2)
        res = getAirports(readCity());
    else {
        pair<double, double> location = readLocation();
        cout << "Raio: " << endl;
        double range = readDouble();
        res = getAirports(location.first, location.second, range);
    }
    return res;
}

/**
 *
 * @return
 */
unordered_set<string> Management::lerRede() const {
    cout << "\nRede de Voos:\n1 - Todas as companhias aéreas\n2 - Especificar companhias aéreas pretendidas\n3 - Especificar companhias aéreas não prentendidas\nOpção: ";
    int option = readInt();
    option = validateInt(option, 1, 3);
    unordered_set<string> res;
    if (option == 2) {
        cout << "\nNúmero de companhias aéreas a incluir: ";
        int n = readInt();
        n = validateInt(n, 1, (int) airlines.size());
        for (int i = 0; i < n; i++)
            res.insert(readAirline().getCode());
    } else if (option == 3) {
        cout << "\nNúmero de companhias aéreas a excluir: ";
        int n = readInt();
        n = validateInt(n, 0, (int) airlines.size() - 1);
        res = getAirlinesCodes();
        for (int i = 0; i < n; i++)
            res.erase(readAirline().getCode());
    }
    return res;
}

/**
 *
 */
void Management::melhorVoo() {
    cout << "Local de Origem";
    list<Airport> origem = lerLocal();
    unordered_set<int> sources = getNumbers(origem);
    cout << "Local de Destino";
    list<Airport> destino = lerLocal();
    unordered_set<int> targets = getNumbers(destino);
    unordered_set<string> filter = lerRede();
    flights.bfs(sources, targets, filter);
    int min = INT_MAX;
    int dest = 0;
    for (const Airport &airport : destino)
        if (flights.getNodes()[airport.getNumber()].distance < min) {
            min = flights.getNodes()[airport.getNumber()].distance;
            dest = airport.getNumber();
        }
    if (min == INT_MAX) {
        cout << "Não é possível voar de acordo com as condições pretendidas." << endl;
        return;
    } else if (min == 1)
        cout << "A melhor maneira de voar de acordo com as condições pretendidas consiste em " << min << " voo:\n" << endl;
    else
        cout << "A melhor maneira de voar de acordo com as condições pretendidas consiste em " << min << " voos:\n" << endl;
    imprimirVoo(flights.getMinPath(dest, min), filter);
}

/**
 *
 * @param path
 * @param filter
 */
void Management::imprimirVoo(const vector<int> &path, const unordered_set<string> &filter) const {
    for (unsigned i = 0; i < path.size() - 1; i++) {
        int current = path[i];
        int next = path[i+1];
        Node node = flights.getNodes()[current];
        airports.find(Airport(node.airportCode))->print();
        cout << "\nVoo " << i + 1 << " via ";
        vector<string> airlinesCodes = flights.getAirlinesCodes(current, next, filter);
        airlines.find(Airline(airlinesCodes.front()))->print();
        for (unsigned j = 1; j < airlinesCodes.size(); j++) {
            cout << " OU ";
            airlines.find(Airline(airlinesCodes[j]))->print();
        }
        cout << endl;
    }
    airports.find(Airport(flights.getNodes()[path.back()].airportCode))->print();
}

/**
 *
 */
void Management::informacoes() {
    Airport airport = readAirport();
    cout << "\nInformações:\n1 - Quantos voos partem do aeroporto?\n2 - Quantas companhias aéreas diferentes partem do aeroporto?\n3 - Quantos destinos diferentes são atingíveis a partir do aeroporto?\n4 - Quantos países diferentes são atingíveis a partir do aeroporto?\n5 - Quantos aeroportos, cidades ou países são atingíveis usando um máximo de Y voos?\n0 - Voltar atrás\nOpção: ";
    int option = readInt();
    option = validateInt(option, 0, 5);
    if (option == 1)
        partidas(airport);
    else if (option == 2)
        companhiasAereas(airport);
    else if (option == 3)
        destinos(airport);
    else if (option == 4)
        paises(airport);
    else if (option == 5)
        yVoos(airport);
}

/**
 *
 * @param airport
 */
void Management::partidas(const Airport &airport) const {
    list<Edge> partidas = flights.getNodes()[airport.getNumber()].adj;
    unsigned n = partidas.size();
    if (n == 1)
        cout << "Parte " << n << " voo do ";
    else
        cout << "Partem " << n << " voos do ";
    airport.print();
    cout << ": " << endl;
    unsigned i = 1;
    for (const Edge &edge : partidas) {
        cout << "Voo " << i++ << " via ";
        airlines.find(Airline(edge.airlineCode))->print();
        cout << " para ";
        airports.find(Airport(flights.getNodes()[edge.dest].airportCode))->print();
        cout << endl;
    }
}

/**
 *
 * @param airport
 */
void Management::companhiasAereas(const Airport &airport) const {
    list<Edge> partidas = flights.getNodes()[airport.getNumber()].adj;
    unordered_set<string> companhiasAereas;
    for (const Edge &edge : partidas)
        companhiasAereas.insert(edge.airlineCode);
    unsigned n = companhiasAereas.size();
    if (n == 1)
        cout << "Parte " << n << " companhia aérea do ";
    else
        cout << "Partem " << n << " companhias aéreas do ";
    airport.print();
    cout << ": " << endl;
    unsigned i = 1;
    for (const string &companhiaAerea : companhiasAereas) {
        cout << i++ << ". ";
        airlines.find(Airline(companhiaAerea))->print();
        cout << endl;
    }
}

/**
 *
 * @param airport
 */
void Management::destinos(const Airport &airport) const {
    list<Edge> partidas = flights.getNodes()[airport.getNumber()].adj;
    unordered_set<Airport, airportHash, airportHash> aeroportos;
    unordered_set<City, cityHash, cityHash> destinos;
    for (const Edge &edge : partidas) {
        Airport destino = *airports.find(Airport(flights.getNodes()[edge.dest].airportCode));
        aeroportos.insert(destino);
        destinos.insert(destino.getCity());
    }
    unsigned n = destinos.size();
    if (n == 1)
        cout << "É atingível " << n << " destino (" << aeroportos.size() << " aeroporto(s)) a partir do ";
    else
        cout << "São atingíveis " << n << " destinos (" << aeroportos.size() << " aeroportos) a partir do ";
    airport.print();
    cout << ": " << endl;
    unsigned i = 1;
    for (const City &city : destinos) {
        cout << i++ << ". ";
        city.print();
        cout << endl;
    }
}

/**
 *
 * @param airport
 */
void Management::paises(const Airport &airport) const {
    list<Edge> partidas = flights.getNodes()[airport.getNumber()].adj;
    unordered_set<string> paises;
    for (const Edge &edge : partidas) {
        Airport destino = *airports.find(Airport(flights.getNodes()[edge.dest].airportCode));
        paises.insert(destino.getCity().getCountry());
    }
    unsigned n = paises.size();
    if (n == 1)
        cout << "É atingível " << n << " país a partir do ";
    else
        cout << "São atingíveis " << n << " países a partir do ";
    airport.print();
    cout << ": " << endl;
    unsigned i = 1;
    for (const string &pais : paises)
        cout << i++ << ". " << pais << endl;
}

/**
 *
 * @param airport
 */
void Management::yVoos(const Airport &airport) {
    cout << "Y: ";
    int y = readInt();
    flights.bfs({airport.getNumber()});
    cout << "\n1 - Aeroportos\n2 - Cidades\n3 - Países\nOpção: ";
    int option = readInt();
    option = validateInt(option, 1, 3);
    if (option == 1)
        yVoosAeroportos(airport, y);
    else if (option == 2)
        yVoosCidades(airport, y);
    else
        yVoosPaises(airport, y);
}

/**
 *
 * @param airport
 * @param y
 */
void Management::yVoosAeroportos(const Airport &airport, const int y) const {
    list<Airport> aeroportos = getAirports(y);
    unsigned n = aeroportos.size();
    if (n == 1)
        cout << "É atingível " << n << " aeroporto a partir do ";
    else
        cout << "São atingíveis " << n << " aeroportos a partir do ";
    airport.print();
    if (y == 1)
        cout << " usando um máximo de " << y << " voo:" << endl;
    else
        cout << " usando um máximo de " << y << " voos:" << endl;
    unsigned i = 1;
    for (const Airport &aeroporto : aeroportos) {
        cout << i++ << ". ";
        aeroporto.print();
        cout << endl;
    }
}

/**
 *
 * @param airport
 * @param y
 */
void Management::yVoosCidades(const Airport &airport, const int y) const {
    list<Airport> aeroportos = getAirports(y);
    unordered_set<City, cityHash, cityHash> cidades;
    for (const Airport &aeroporto : aeroportos)
        cidades.insert(aeroporto.getCity());
    unsigned n = cidades.size();
    if (n == 1)
        cout << "É atingível " << n << " cidade a partir do ";
    else
        cout << "São atingíveis " << n << " cidades a partir do ";
    airport.print();
    if (y == 1)
        cout << " usando um máximo de " << y << " voo:" << endl;
    else
        cout << " usando um máximo de " << y << " voos:" << endl;
    unsigned i = 1;
    for (const City &city : cidades) {
        cout << i++ << ". ";
        city.print();
        cout << endl;
    }
}

/**
 *
 * @param airport
 * @param y
 */
void Management::yVoosPaises(const Airport &airport, const int y) const {
    list<Airport> aeroportos = getAirports(y);
    unordered_set<string> paises;
    for (const Airport &aeroporto : aeroportos)
        paises.insert(aeroporto.getCity().getCountry());
    unsigned n = paises.size();
    if (n == 1)
        cout << "É atingível " << n << " país a partir do ";
    else
        cout << "São atingíveis " << n << " países a partir do ";
    airport.print();
    if (y == 1)
        cout << " usando um máximo de " << y << " voo:" << endl;
    else
        cout << " usando um máximo de " << y << " voos:" << endl;
    unsigned i = 1;
    for (const string &pais : paises)
        cout << i++ << ". " << pais << endl;
}

/**
 *
 */
void Management::pontosArticulacao() {
    int index = 1;
    unordered_set<string> points;
    flights.unvisitNodes();
    for (int v = 1; v <= flights.getN(); v++)
        if (flights.getNodes()[v].num == 0) {
            cout << "dfs called for " << v << endl;
            flights.dfs_art(v, true, index, points);
        }
    unsigned n = points.size();
    cout << "A rede de voos tem " << n << " pontos de articulação:" << endl;
    unsigned i = 1;
    for (const string &point : points) {
        cout << i++ << ". ";
        airports.find(Airport(point))->print();
        cout << endl;
    }
}