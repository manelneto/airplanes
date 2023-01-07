//
// Created by manue on 29/12/2022.
//

#include "Management.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

/**Construtor sem parâmetros. Constrói um objeto de gestão com aeroportos, companhias aéreas e voos lidos de ficheiros.
 * <br>Complexidade Temporal: O()
 */
Management::Management() {
    readAirportsFile();
    readAirlinesFile();
    readFlightsFile();
}

/**Lê o ficheiro de aeroportos e cria a tabela de hash de cidades, a tabela de hash de aeroportos e os nós do grafo de voos.
 * <br>Complexidade Temporal: O(n), sendo n o número de linhas do ficheiro de aeroportos
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

/**Lê o ficheiro de companhias aéreas e cria a tabela de hash de companhias aéreas.
 * <br>Complexidade Temporal: O(n), sendo n o número de linhas do ficheiro de companhias aéreas
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

/**Lê o ficheiro de voos e cria as arestas do grafo de voos.
 * <br>Complexidade Temporal: O(n), sendo n o número de linhas do ficheiro de voos
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
        if (source != airports.end() && target != airports.end())
            flights.addEdge(source->getNumber(), target->getNumber(), fields[2]);
    }
    cout << "Leitura de ficheiro flights.csv bem-sucedida." << endl;
}

/**Calcula a distância entre dois pontos dadas as suas latitudes e longitudes.
 * <br>Complexidade Temporal: O(1)
 * @param lat1 latitude do ponto 1
 * @param lon1 longitude do ponto 1
 * @param lat2 latitude do ponto 2
 * @param lon2 longitude do ponto 2
 * @return distância entre os pontos 1 e 2
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

/**Verifica se str é um número inteiro não negativo.
 * <br>Complexidade Temporal: O(n), sendo n o comprimento de str
 * @param str string a verificar
 * @return true se str é um número inteiro não negativo, false caso contrário
 */
bool Management::isInt(const string &str) {
    for (const char &ch : str)
        if (!isdigit(ch))
            return false;
    return true;
}

/**Verifica se str é um número decimal.
 * <br>Complexidade Temporal: O(n), sendo n o comprimento de str
 * @param str string a verificar
 * @return true se str é um número decimal, false caso contrário
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

/**Retorna str com todos os caracteres convertidos para maiúscula.
 * <br>Complexidade Temporal: O(n), sendo n o comprimento de str
 * @param str string a copiar e converter os caracteres para maiúscula
 * @return str com todos os caracteres convertidos para maiúscula
 */
string Management::toUpper(const string &str) {
    string upper;
    for (const char &ch : str)
        upper += (char) toupper(ch);
    return upper;
}

/**Lê o input do utilizador.
 * <br>Complexidade Temporal: O(n), sendo n o comprimento do input do utilizador
 * @return input do utilizador
 */
string Management::readInput() {
    string s;
    getline(cin, s);
    cout << endl;
    return s;
}

/**Lê o input do utilizador, forçando a que seja um número inteiro não negativo.
 * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @return número inteiro não negativo introduzido pelo utilizador
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

/**Lê o input do utilizador, forçando a que seja um número.
 * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @return número introduzido pelo utilizador
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

/**Valida um número inteiro, isto é, verifica se n pertence ao intervalo [min, max]. Enquanto o número for inválido, tenta ler um número válido.
 * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @param n número a validar
 * @param min limite inferior do intervalo de números válidos
 * @param max limite superior do intervalo de números válidos
 * @return número inteiro válido introduzido pelo utilizador
 */
int Management::validateInt(int n, int min, int max) {
    while (n < min || n > max) {
        cout << "O número inserido não é válido (deve pertencer ao intervalo [" << min << ", " << max << "]). Tente novamente: ";
        n = readInt();
    }
    return n;
}

/**Valida um número decimal, isto é, verifica se n pertence ao intervalo [min, max]. Enquanto o número for inválido, tenta ler um número válido.
 * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @param n número a validar
 * @param min limite inferior do intervalo de números válidos
 * @param max limite superior do intervalo de números válidos
 * @return número decimal válido introduzido pelo utilizador
 */
double Management::validateDouble(double n, double min, double max) {
    while (n < min || n > max) {
        cout << "O número inserido não é válido (deve pertencer ao intervalo [" << min << ", " << max << "]). Tente novamente: ";
        n = readDouble();
    }
    return n;
}

/**Lê um aeroporto através do seu código IATA, forçando a que ele exista.
 * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @return aeroporto existente introduzido pelo utilizador
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

/**Lê uma companhia aérea através do seu código ICAO, forçando a que ela exista.
 * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @return companhia aérea existente introduzido pelo utilizador
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

/**Lê uma cidade através do seu nome e país, forçando a que ela exista.
 * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @return cidade existente introduzido pelo utilizador
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

/**Lê uma localização através da sua latitude e longitude, forçando a que ela seja válida.
 * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @return localização (par latitude-longitude) válida introduzida pelo utilizador
 */
pair<double, double> Management::readLocation() {
    cout << "Latitude: ";
    double lat = readDouble();
    lat = validateDouble(lat, -90.0, 90.0);
    cout << "Longitude: ";
    double lon = readDouble();
    lon = validateDouble(lon, -180.0, 180.0);
    return make_pair(lat, lon);
}

/**Retorna os aeroportos de uma cidade.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho de airports
 * @param city cidade
 * @return aeroportos da cidade
 */
list<Airport> Management::getAirports(const City &city) const {
    list<Airport> res;
    for (const Airport &airport: airports)
        if (airport.getCity() == city)
            res.push_back(airport);
    return res;
}

/**Retorna os aeroportos a menos de range quilómetros de uma localização.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho de airports
 * @param latitude latitude da localização
 * @param longitude longitude da localização
 * @param range distância máxima da localização para aceitar aeroporto
 * @return aeroportos a menos de range quilómetros da localização dada pelo par latitude-longitude
 */
list<Airport> Management::getAirports(const double latitude, const double longitude, const double range) const {
    list<Airport> res;
    for (const Airport &airport: airports)
        if (haversine(latitude, longitude, airport.getLatitude(), airport.getLongitude()) < range)
            res.push_back(airport);
    return res;
}

/**Retorna os aeroportos cuja distância calculada pertence ao intervalo ]0, y].
 * <br>Complexidade Temporal: O(n), sendo n o tamanho de nós do grafo flights
 * @param y distância máxima para aceitar aeroporto
 * @return aeroportos cuja distância calculada pertence ao intervalo ]0, y]
 */
list<Airport> Management::getAirports(const int y) const {
    list<Airport> res;
    for (const Node &node : flights.getNodes())
        if (node.distance <= y && node.distance > 0)
            res.push_back(*airports.find(Airport(node.airportCode)));
    return res;
}

/**Retorna os números dos aeroportos em airports.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho de airports
 * @param airports aeroportos
 * @return números dos aeroportos em airports
 */
unordered_set<int> Management::getNumbers(const list<Airport> &airports) {
    unordered_set<int> numbers;
    for (const Airport &airport : airports)
        numbers.insert(airport.getNumber());
    return numbers;
}

/**Retorna os códigos ICAO das companhias aéreas em airlines.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho de airlines
 * @return códigos ICAO das companhias aéreas em airlines
 */
unordered_set<string> Management::getAirlinesCodes() const {
    unordered_set<string> airlinesCodes;
    for (const Airline &airline : airlines)
        airlinesCodes.insert(airline.getCode());
    return airlinesCodes;
}

/**Apresenta o menu principal e permite selecionar uma das opções apresentadas.
 * <br>Complexidade Temporal: amplamente variável de acordo com o input
 * @return 0 se o utilizador pretender sair, 1 caso contrário
 */
int Management::menu() {
    cout << "\nMenu Principal:\n1 - Melhor maneira de voar entre dois locais\n2 - Informações sobre um aeroporto\n3 - Calcular estatísticas globais da rede\n4 - Calcular os pontos de articulação existentes na rede\n0 - Sair\nOpção: ";
    int option = readInt();
    option = validateInt(option, 0, 4);
    if (option == 1)
        melhorVoo();
    else if (option == 2)
        informacoes();
    else if (option == 3)
        estatisticas();
    else if (option == 4)
        pontosArticulacao();
    else
        return 0;
    return 1;
}

/**Lê um local (aeroporto, cidade ou localização) e retorna os aeroportos desse local.
 * <br>Complexidade Temporal: O(n), sendo n o número de aeroportos do local lido
 * @return aeroportos do local lido
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

/**Lê uma rede de voos (códigos ICAO das companhias aéreas a incluir ou a excluir) e retorna os códigos ICAO das companhias aéreas dessa rede de voos.
 * <br>Complexidade Temporal: O(n), sendo n o número de companhias aéreas da rede de voos lida
 * @return códigos ICAO das companhias aéreas da rede de voos lida
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

/**Determina a melhor maneira de voar entre entre dois locais lidos do utilizador (de um para o outro), através de uma rede de voos lida do utilizador.
 * <br>Complexidade Temporal: O(|V| + |E|), sendo V o número de vértices do grafo flights e E o número de arestas do grafo flights
 */
void Management::melhorVoo() {
    cout << "Local de Origem";
    list<Airport> origem = lerLocal();
    unordered_set<int> sources = getNumbers(origem);
    cout << "Local de Destino";
    list<Airport> destino = lerLocal();
    unordered_set<int> targets = getNumbers(destino);
    unordered_set<string> filter = lerRede();
    flights.bfs_flights(sources, targets, filter);
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

/**Imprime um voo: caminho de nós/aeroportos através de arestas/companhias aéreas.
 * <br>Complexidade Temporal: O(n * m), sendo n o tamanho de path e m o maior tamanho de entre as companhias aéreas possíveis (e filtradas) para cada voo
 * @param path caminho de nós/aeroportos a imprimir
 * @param filter filtro de companhias aéreas a incluir
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

/**Apresenta o menu de informações sobre um aeroporto lido e permite selecionar uma das opções apresentadas.
 * <br>Complexidade Temporal: amplamente variável de acordo com o input
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

/**Determina e imprime quantos e quais voos existem a partir do aeroporto em análise.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho da lista de adjacências do nó do grafo flights correspondente ao aeroporto em análise
 * @param airport aeroporto em análise
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

/**Determina e imprime quantas e quais companhias aéreas partem do aeroporto em análise.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho da lista de adjacências do nó do grafo flights correspondente ao aeroporto em análise
 * @param airport aeroporto em análise
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

/**Determina e imprime quantos e quais destinos (cidades) são atingíveis a partir do aeroporto em análise.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho da lista de adjacências do nó do grafo flights correspondente ao aeroporto em análise
 * @param airport aeroporto em análise
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

/**Determina e imprime quantos e quais países são atingíveis a partir do aeroporto em análise.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho da lista de adjacências do nó do grafo flights correspondente ao aeroporto em análise
 * @param airport aeroporto em análise
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

/**Determina as distâncias de todos os aeroportos ao aeroporto em análise, lê um valor Y do utilizador para utilização futura e permite selecionar uma das opções apresentadas.
 * <br>Complexidade Temporal: O(|V| + |E|), sendo V o número de vértices do grafo flights e E o número de arestas do grafo flights
 * @param airport aeroporto em análise
 */
void Management::yVoos(const Airport &airport) {
    cout << "Y: ";
    int y = readInt();
    flights.bfs_flights({airport.getNumber()});
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

/**Determina e imprime quantos e quais aeroportos são atingíveis a partir do aeroporto de partida usando um máximo de Y voos.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho de nós do grafo flights
 * @param airport aeroporto de partida
 * @param y número máximo de voos para aceitar aeroporto
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

/**Determina e imprime quantas e quais cidades são atingíveis a partir do aeroporto de partida usando um máximo de Y voos.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho de nós do grafo flights
 * @param airport aeroporto de partida
 * @param y número máximo de voos para aceitar aeroporto
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

/**Determina e imprime quantos e quais países são atingíveis a partir do aeroporto em análise usando um máximo de Y voos.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho de nós do grafo flights
 * @param airport aeroporto de partida
 * @param y número máximo de voos para aceitar aeroporto
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

/**Cacula e imprime estatísticas globais da rede de voos: número de aeroportos, número de voos, número de companhias aéreas, diâmetro, aeroporto com mais voos, máximo de voos por aeroporto, média de voos por aeroporto (grau médio) e número de componentes fortemente conexos.
 * <br>Complexidade Temporal: O(|V| * (2|V| + |E|)), sendo V o número de vértices do grafo flights e E o número de arestas do grafo flights
 */
void Management::estatisticas() {
    cout << "\nAeroportos: " << airports.size();
    unsigned nVoos = 0;
    for (const Node &node : flights.getNodes())
        nVoos += node.adj.size();
    cout << "\nVoos: " << nVoos;
    cout << "\nCompanhias Aéreas: " << airlines.size();
    cout << "\nDiâmetro: " << flights.diameter();
    pair<Airport, int> pair = aeroportoMaisVoos();
    cout << "\nAeroporto com mais voos: ";
    pair.first.print();
    cout << "\nMáximo de voos por aeroporto: " << pair.second;
    cout << "\nMédia de voos por aeroporto (grau médio): " << 1.0 * nVoos/airports.size();
    cout << "\nComponentes Fortemente Conexos: " << componentesFortementeConexos() << endl;
}

/**Calcula e retorna o aeroporto com mais voos e o número de voos desse aeroporto.
 * <br>Complexidade Temporal: O(|V|), sendo V o número de vértices do grafo flights
 * @return aeroporto com mais voos e número de voos desse aeroporto
 */
pair<Airport, int> Management::aeroportoMaisVoos() const {
    string airportCode;
    unsigned max = 0;
    for (int v = 1; v <= flights.getN(); v++) {
        Node node = flights.getNodes()[v];
        if (node.adj.size() > max) {
            airportCode = node.airportCode;
            max = node.adj.size();
        }
    }
    Airport airport = *airports.find(airportCode);
    return make_pair(airport, max);
}

/**Calcula e retorna o número de componentes fortemente conexos da rede de voos.
 * <br>Complexidade Temporal: O(|V| + |E|), sendo V o número de vértices do grafo flights e E o número de arestas do grafo flights
 * @return número de componentes fortemente conexos da rede de voos
 */
int Management::componentesFortementeConexos() {
    int scc = 0;
    int index = 1;
    flights.unvisitNodes();
    stack<int> s;
    for (int v = 1; v <= flights.getN(); v++)
        if (flights.getNodes()[v].num == 0)
            flights.dfs_scc(v, index, s, scc);
    return scc;
}

/**Calcula e imprime os pontos de articulação existentes na rede de voos.
 * <br>Complexidade Temporal: O(|V| + |E|), sendo V o número de vértices do grafo flights e E o número de arestas do grafo flights
 */
void Management::pontosArticulacao() {
    int index = 1;
    unordered_set<string> points;
    flights.unvisitNodes();
    for (int v = 1; v <= flights.getN(); v++)
        if (flights.getNodes()[v].num == 0)
            flights.dfs_art(v, true, index, points);
    unsigned n = points.size();
    cout << "A rede de voos tem " << n << " pontos de articulação:" << endl;
    unsigned i = 1;
    for (const string &point : points) {
        cout << i++ << ". ";
        airports.find(Airport(point))->print();
        cout << endl;
    }
}
