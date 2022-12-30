//
// Created by manue on 29/12/2022.
//

#include "Graph.h"
#include <queue>

using namespace std;

Graph::Graph() {}

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int airline) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, airline});
    if (!hasDir) nodes[dest].adj.push_back({src, airline});
}

// Depth-First Search
void Graph::dfs(int v) {
    // show node order
    // cout << v << " ";
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

// Breadth-First Search
void Graph::bfs(int v) {
    for (int i=1; i<=n; i++) nodes[i].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        // show node order
        //cout << u << " ";
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}
