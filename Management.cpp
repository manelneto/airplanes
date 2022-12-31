//
// Created by manue on 29/12/2022.
//

#include "Management.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

Management::Management() {
    readAirportsFile();
    readAirlinesFile();
    readFlightsFile();
}

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

bool Management::isInt(const string &str) {
    for (const char &ch : str)
        if (!isdigit(ch))
            return false;
    return true;
}

bool Management::isDouble(const string &str) {
    for (const char &ch : str)
        if (!isdigit(ch) && ch != '.')
            return false;
    return true;
}

void Management::toUpper(string &str) {
    for (char &ch : str)
        ch = toupper(ch);
}

string Management::readString() {
    string s;
    cin >> s;
    cout << endl;
    return s;
}

int Management::readInt() {
    string s = readString();
    while (!isInt(s)) {
        cout << "Deve inserir um número inteiro não negativo. Tente novamente." << endl;
        s = readString();
    }
    int n = stoi(s);
    return n;
}

double Management::readDouble() {
    string s = readString();
    while (!isDouble(s)) {
        cout << "Deve inserir um número e o separador de casas decimais deve ser o ponto (.). Tente novamente." << endl;
        s = readString();
    }
    double n = stod(s);
    return n;
}

int Management::validateOption(int option, int min, int max) {
    while (option < min || option > max) {
        cout << "O número inserido não é uma opção válida. Tente novamente." << endl;
        option = readInt();
    }
    return option;
}

Airport Management::readAirport() const {
    cout << "Código IATA do Aeroporto: ";
    string code = readString();
    toUpper(code);
    Airport airport = Airport(code);
    while (airports.find(airport) == airports.end()) {
        cout << "Aeroporto não encontrado. Tente novamente." << endl;
        airport = readAirport();
    }
    return *airports.find(airport);
}

Airline Management::readAirline() const {
    cout << "Código ICAO da Companhia Aérea: ";
    string code = readString();
    toUpper(code);
    Airline airline = Airline(code);
    while (airlines.find(airline) == airlines.end()) {
        cout << "Companhia Aérea não encontrada. Tente novamente." << endl;
        airline = readAirline();
    }
    return *airlines.find(airline);
}

City Management::readCity() const {
    cout << "Cidade: ";
    string cityName = readString();
    cout << "País: ";
    string country = readString();
    City city(cityName, country);
    while (cities.find(city) == cities.end()) {
        cout << "Cidade não encontrada. Tente novamente." << endl;
        city = readCity();
    }
    return *cities.find(city);
}

pair<double, double> Management::readLocation() {
    cout << "Latitude: ";
    double lat = readDouble();
    cout << "Longitude: ";
    double lon = readDouble();
    return make_pair(lat, lon);
}

list<Airport> Management::getAirports(const City &city) {
    list<Airport> res;
    for (const Airport &airport: airports)
        if (airport.getCity() == city)
            res.push_back(airport);
    return res;
}

list<Airport> Management::getAirports(double latitude, double longitude, double range) {
    list<Airport> res;
    for (const Airport &airport: airports)
        if (haversine(latitude, longitude, airport.getLatitude(), airport.getLongitude()) < range)
            res.push_back(airport);
    return res;
}

list<Airport> Management::lerLocal() {
    cout << "\nLocal:\n1 - Aeroporto\n2 - Cidade\n3 - Localização\nOpção: ";
    int option = readInt();
    option = validateOption(option, 1, 3);
    list<Airport> res;
    switch (option) {
        case 1:
            res.push_back(readAirport());
            break;
        case 2: {
            City city = readCity();
            res = getAirports(city);
            break;
        }
        case 3: {
            pair<double, double> location = readLocation();
            cout << "Raio: " << endl;
            double range = readDouble();
            res = getAirports(location.first, location.second, range);
            break;
        }
        default:
            return res;
    }
    return res;
}

int Management::menu() {
    cout << "\nMenu Principal:\n1 - Melhor maneira de voar entre dois locais\n2 - Informações sobre um aeroporto\n0 - Sair\nOpção: ";
    int option = readInt();
    option = validateOption(option, 0, 2);
    switch (option) {
        case 1:
            melhorVoo();
            break;
        case 2:
            informacoes();
            break;
        default:
            return 0;
    }
    return 1;
}

void Management::melhorVoo() {
    cout << "Local de Origem" << endl;
    list<Airport> origem = lerLocal();
    cout << "Local de Destino" << endl;
    list<Airport> destino = lerLocal();
    list<int> sources;
    for (const Airport &airport: origem)
        sources.push_back(airport.getNumber());
    flights.univisitNodes();
    flights.bfs(sources);
    int min = INT_MAX;
    int best = 0;
    for (const Airport &airport: destino)
        if (flights.getNodes()[airport.getNumber()].distance < min) {
            min = flights.getNodes()[airport.getNumber()].distance;
            best = airport.getNumber();
        }
    cout << min << " voos" << endl;
}

void Management::informacoes() {
}