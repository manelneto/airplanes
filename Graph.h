//
// Created by manue on 30/12/2022.
//

#ifndef AIRPLANES_GRAPH_H
#define AIRPLANES_GRAPH_H


#include <string>
#include <list>
#include <vector>

class Graph {
public:
    Graph(int nodes);
    void addNode(const std::string &airportCode);
    void addEdge(int source, int target, const std::string &airlineCode);
    void dfs(int v);
    void bfs(int v);
private:
    struct Edge {
        int dest;
        std::string airlineCode;
    };
    struct Node {
        std::string airportCode;
        std::list<Edge> adj;
        bool visited;
    };
    int n;
    std::vector<Node> nodes;
};


#endif //AIRPLANES_GRAPH_H
