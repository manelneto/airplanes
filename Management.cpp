//
// Created by manue on 29/12/2022.
//

#include "Management.h"
#include <fstream>
#include <sstream>
#include <iostream>

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
        string city = fields[2];
        string country = fields[3];
        double latitude = stod(fields[4]);
        double longitude = stod(fields[5]);
        Airport airport = Airport(code, name, city, country, latitude, longitude, number++);
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