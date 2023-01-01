//
// Created by manue on 30/12/2022.
//

#ifndef AIRPLANES_GRAPH_H
#define AIRPLANES_GRAPH_H


#include <string>
#include <list>
#include <unordered_set>
#include <vector>

struct Edge {
    int dest;
    std::string airlineCode;
};

struct Node {
    std::string airportCode;
    std::list<Edge> adj;
    bool visited;
    int distance;
    int previous;
};

class Graph {
public:
    Graph(int n);
    const std::vector<Node> &getNodes() const;
    std::vector<std::string> getAirlinesCodes(int src, int dest, const std::unordered_set<std::string> &filter = {}) const;
    std::vector<int> getMinPath(int dest, int min) const;
    void addNode(const std::string &airportCode);
    void addEdge(int source, int target, const std::string &airlineCode);
    void bfs(const std::unordered_set<int> &sources, const std::unordered_set<int> &targets, const std::unordered_set<std::string> &filter = {});
private:
    int n;
    std::vector<Node> nodes;
    void unvisitNodes();
};


#endif //AIRPLANES_GRAPH_H
