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
        int dest;
        int airline;
    };

    struct Node {
        int airport;
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirected; true: directed
    std::vector<Node> nodes; // The list of nodes being represented

public:
    Graph();
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int airlne);

    // Depth-First Search
    void dfs(int v);

    // Breadth-First Search
    void bfs(int v);
};


#endif //AIRPLANES_GRAPH_H
