//
// Created by manue on 30/12/2022.
//

#include "Graph.h"
#include <queue>

using namespace std;

Graph::Graph(int num) : n(num), nodes(num+1) {}

void Graph::addNode(const std::string &airportCode) {
    n += 1;
    nodes.push_back({airportCode, {}, false});
}

void Graph::addEdge(int source, int target, const std::string &airlineCode) {
    if (source < 1 || source > n || target < 1 || target > n) return;
    nodes[source].adj.push_back({target, airlineCode});
}

void Graph::dfs(int v) {
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

void Graph::bfs(int v) {
    for (int i = 1; i <= n; i++)
        nodes[i].visited = false;
    queue<int> q;
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}