//
// Created by manue on 29/12/2022.
//

#ifndef AIRPLANES_GRAPH_H
#define AIRPLANES_GRAPH_H


#include <list>
#include <vector>
#include <iostream>

class Graph {
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
    };

    struct Node {
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
        char color;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirected; true: directed
    std::vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1);

    // Depth-First Search: example implementation
    void dfs(int v, bool & b);
};


#endif //AIRPLANES_GRAPH_H
