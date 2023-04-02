#include "headers/Database.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void Database::loadWithoutFilters() {
    readStations();
    readNetwork();
}

void Database::loadWithFilters(set<string> stations, set<string> lines, ServiceType service) {
    readStations(stations, lines);
    readNetwork(service);
}

void Database::readStations() {
    ifstream file("../data/stations.csv");
    file.ignore(1000, '\n'); // ignore first line

    if (!file.is_open()) {
        cout << "Error opening stations.csv" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ';')) {
            fields.push_back(field);
        }
        if (fields.size() != 5) {
            cout << "The following line is invalid: " << line << endl;
            return;
        }

        string name = fields[0];
        string district = fields[1];
        string municipality = fields[2];
        string township = fields[3];
        string line = fields[4];

        Station *station = new Station(name, district, municipality, township, line);
        graph.addNode(*station);
        nameToStation[name] = station;
    }
    file.close();
    return;
}

void Database::readStations(set<string> stations, set<string> lines) {
    ifstream file("../data/stations.csv");
    file.ignore(1000, '\n'); // ignore first line

    if (!file.is_open()) {
        cout << "Error opening stations.csv" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ';')) {
            fields.push_back(field);
        }
        if (fields.size() != 5) {
            cout << "The following line is invalid: " << line << endl;
            return;
        }

        string name = fields[0];
        string district = fields[1];
        string municipality = fields[2];
        string township = fields[3];
        string line = fields[4];

        if ((line.empty() || (lines.find(line) != lines.end())) && (stations.empty() || (stations.find(name) != stations.end()))) {
            Station *station = new Station(name, district, municipality, township, line);
            graph.addNode(*station);
            nameToStation[name] = station;
        }
    }
    file.close();
    return;
}

void Database::readNetwork() {
    ifstream file("../data/network.csv");
    file.ignore(1000, '\n'); // ignore first line

    if (!file.is_open()) {
        cout << "Error opening network.csv" << endl;
        return;
    }

    string line;
    int lineCount = 0;
    while (getline(file, line)) {
        lineCount++;
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ';')) {
            fields.push_back(field);
        }
        if (fields.size() != 4) {
            cout << "Line" << lineCount << " is invalid: " << line << endl;
        }

        string orig = fields[0];
        string dest = fields[1];
        int capacity = stoi(fields[2]);
        string serviceType = fields[3];
        ServiceType service;
            if(serviceType == "STANDARD")
                service = STANDARD;
            else if(serviceType == "ALFA_PENDULAR")
                service = ALFA_PENDULAR;
            else{
                cout << "Line" << lineCount << " service type is invalid: " << line << endl;
            }

        Station *origStation = nameToStation[orig];
        Station *destStation = nameToStation[dest];

        if (origStation == nullptr){
            cout << "Line" << lineCount << " station" << orig << "wasn't initialized: " << line << endl;
            continue;
        }
        if (destStation == nullptr){
            cout << "Line" << lineCount << " station" << dest << "wasn't initialized: " << line << endl;
            continue;
        }

        graph.addEdge(*origStation, *destStation, capacity, service);
    }
    file.close();
    return;
}

void Database::readNetwork(ServiceType serviceFilter) {
    ifstream file("../data/network.csv");
    file.ignore(1000, '\n'); // ignore first line

    if (!file.is_open()) {
        cout << "Error opening network.csv" << endl;
        return;
    }

    string line;
    int lineCount = 0;
    while (getline(file, line)) {
        lineCount++;
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ';')) {
            fields.push_back(field);
        }
        if (fields.size() != 4) {
            cout << "Line" << lineCount << " is invalid: " << line << endl;
        }

        string orig = fields[0];
        string dest = fields[1];
        int capacity = stoi(fields[2]);
        string serviceType = fields[3];

        ServiceType service;
        if(serviceType == "STANDARD")
            service = STANDARD;
        else if(serviceType == "ALFA_PENDULAR")
            service = ALFA_PENDULAR;
        else{
            cout << "Line" << lineCount << " service type is invalid: " << line << endl;
        }

        Station *origStation = nameToStation[orig];
        Station *destStation = nameToStation[dest];

        if(serviceFilter != ServiceType::NONE){
            if(service != serviceFilter || origStation == nullptr || destStation == nullptr)
                continue;
        }

        graph.addEdge(*origStation, *destStation, capacity, service);
    }
    file.close();
    return;
}

void Database::printNodes() {
    map<string, Node*> nodes = graph.getNodeMap();
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        cout << it->first << endl;
    }
}