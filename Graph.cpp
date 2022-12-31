//
// Created by manue on 30/12/2022.
//

#include "Graph.h"
#include <queue>

using namespace std;

Graph::Graph(int n) : n(n), nodes(n + 1) {}

const vector<Node> &Graph::getNodes() const {
    return nodes;
}

void Graph::addNode(const std::string &airportCode) {
    n += 1;
    nodes.push_back({airportCode, {}, false});
}

#include <iostream>
void Graph::addEdge(int source, int target, const std::string &airlineCode) {
    if (source < 1 || source > n || target < 1 || target > n)
        return;
    nodes[source].adj.push_back({target, airlineCode});
}

void Graph::univisitNodes() {
    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
        nodes[i].distance = 0;
    }
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
    queue<int> q;
    q.push(v);
    nodes[v].distance = 0;
    nodes[v].visited = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
            }
        }
    }
}

void Graph::bfs(list<int> sources) {
    queue<int> q;
    for (int v : sources) {
        q.push(v);
        nodes[v].distance = 0;
        nodes[v].visited = true;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
            }
        }
    }
}