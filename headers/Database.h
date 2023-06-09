#ifndef PROJECT_DA_DATABASE_H
#define PROJECT_DA_DATABASE_H

#include "Graph.h"
#include <unordered_map>

/**
 * @brief Class that reads the files and contains the dataStructures created
 */
class Database {
    public:
        Database() = default;
        void loadWithoutFilters();
        void loadWithFilters(set<string> stations, set<string> lines);
        Station* getStation(string stationName);

        vector<pair<Node *, Node *>> maxFlowAllPairs(int *maxFlow);
        map<string, set<string>> getDistrictToMunicipalities();
        set<string> getStationsFromMunicipality(string municipality);
        map<string, vector<int>> getStationToNumTrains();

        int getMaxFlowBetweenStations(Station* station1, Station* station2);
        stack<Edge*> getMinCostFlow(Station* station1, Station* station2, double *flow, double *cost);
        int getMaxTrainsStation(Station* station);
        void maxTrainAllStations();

        vector<pair<string, int>> getTopMunicipalities(int k);
        vector<pair<string, int>> getTopDistricts(int k);

        bool checkConnection(Station* station1, Station* station2, int& curCapacity);
        void changeCapacity(Station* station1, Station* station2, int newCapacity);

    private:
        Graph graph;
        unordered_map<string, Station*> nameToStation;
        map<string, set<string>> municipalityToStations;
        map<string, set<string>> districtToMunicipalities;
        map<string, vector<int>> stationToNumTrains;

        void readStations(set<string> stations, set<string> lines);
        void readNetwork();
};

#endif //PROJECT_DA_DATABASE_H
