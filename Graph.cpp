//
// Created by manue on 29/12/2022.
//

#include "Graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

// Depth-First Search: example implementation
void Graph::dfs(int v, bool & b) {
    // show node order
    // cout << v << " ";
    nodes[v].color = 'g';
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (nodes[w].color == 'g')
            b = true;
            //cout << "Cycle found!";
        else if (nodes[w].color == 'w')
            dfs(w, b);
    }
    nodes[v].color = 'b';
}