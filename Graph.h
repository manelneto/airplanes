//
// Created by manue on 30/12/2022.
//

#ifndef AIRPLANES_GRAPH_H
#define AIRPLANES_GRAPH_H


#include <string>
#include <list>
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
};

class Graph {
public:
    Graph(int n);
    const std::vector<Node> &getNodes() const;
    void addNode(const std::string &airportCode);
    void addEdge(int source, int target, const std::string &airlineCode);
    void univisitNodes();
    void dfs(int v);
    void bfs(int v);
    void bfs(std::list<int> sources);
private:
    int n;
    std::vector<Node> nodes;
};


#endif //AIRPLANES_GRAPH_H
