#ifndef PROJECT_DA_NODEEDGE_H
#define PROJECT_DA_NODEEDGE_H

#include "Station.h"

#include <vector>
#include "ServiceType.h"

class Edge;

class Node{
    public:
        Node(Station& station);
        bool operator<(Node& node);

        Station& getStation();
        vector<Edge *> getAdj();
        bool isVisited();
        bool isProcessing();
        unsigned int getIndegree();
        double getDistance();
        Edge *getPath();
        vector<Edge *> getIncoming();
        string getStationName();

        void setVisited(bool visited);
        void setProcessing(bool processing);
        void setIndegree(unsigned int indegree);
        void setDistance(double distance);
        void setPath(Edge *path);
        Edge *addEdge(Node *dest, int capacity, ServiceType service);
        bool removeEdgeTo(Node *dest);


    private:
        Station& station;
        vector<Edge *> adj;

        bool visited = false;
        bool processing = false;
        unsigned int indegree;
        double distance = 0;
        Edge *path = nullptr;

        vector<Edge *> incoming;
        int queueIndex = 0; // required by MutablePriorityQueue
};

class Edge {
public:
    Edge(Node *orig, Node *dest, int capacity, ServiceType service);

    Node* getDest();
    int getCapacity();
    bool isSelected();
    ServiceType getService();
    Node* getOrig();
    Edge* getReverse();
    double getFlow();

    void setFlow(double flow);
    void setReverse(Edge* reverse);
    void setSelected(bool selected);

    bool operator<(Edge& edge);

private:
    Node * dest;
    int capacity;
    ServiceType service;

    bool selected = false;

    double flow;

    //Used for bidirectional edges
    Edge *reverse = nullptr;
    Node *orig;
};



#endif //PROJECT_DA_NODEEDGE_H