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

vector<string> Graph::getAirlinesCodes(int src, int dest, unordered_set<string> desiredAirlinesCodes) const {
    vector<string> airlinesCodes;
    for (const Edge &edge : nodes[src].adj)
        if (edge.dest == dest && (desiredAirlinesCodes.empty() || desiredAirlinesCodes.find(edge.airlineCode) != desiredAirlinesCodes.end()))
            airlinesCodes.push_back(edge.airlineCode);
    return airlinesCodes;
}


void Graph::addNode(const std::string &airportCode) {
    n += 1;
    nodes.push_back({airportCode, {}, false});
}

void Graph::addEdge(int source, int target, const std::string &airlineCode) {
    if (source < 1 || source > n || target < 1 || target > n)
        return;
    nodes[source].adj.push_back({target, airlineCode});
}

void Graph::univisitNodes() {
    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
        nodes[i].distance = INT_MAX;
    }
}

void Graph::bfs(const unordered_set<int> &sources, const unordered_set<int> &targets, const std::unordered_set<std::string> &airlinesCodes, vector<int> &previous) {
    univisitNodes();
    queue<int> q;
    for (int v : sources) {
        q.push(v);
        nodes[v].distance = 0;
        nodes[v].visited = true;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const Edge &edge : nodes[u].adj) {
            if (airlinesCodes.empty() || airlinesCodes.find(edge.airlineCode) != airlinesCodes.end()) {
                int w = edge.dest;
                if (!nodes[w].visited) {
                    q.push(w);
                    nodes[w].visited = true;
                    nodes[w].distance = nodes[u].distance + 1;
                    previous[w] = u;
                }
                if (targets.find(edge.dest) != targets.end())
                    return;
            }
        }
    }
}
