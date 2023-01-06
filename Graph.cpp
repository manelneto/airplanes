//
// Created by manue on 30/12/2022.
//

#include "Graph.h"
#include <queue>

using namespace std;

/**
 *
 * @param n
 */
Graph::Graph(int n) : n(n), nodes(n + 1) {}

/**
 *
 * @return
 */
int Graph::getN() const {
    return n;
}

/**
 *
 * @return
 */
const vector<Node> &Graph::getNodes() const {
    return nodes;
}

/**
 *
 * @param src
 * @param dest
 * @param filter
 * @return
 */
vector<string> Graph::getAirlinesCodes(int src, int dest, const unordered_set<string> &filter) const {
    vector<string> airlinesCodes;
    for (const Edge &edge : nodes[src].adj)
        if (edge.dest == dest && (filter.empty() || filter.find(edge.airlineCode) != filter.end()))
            airlinesCodes.push_back(edge.airlineCode);
    return airlinesCodes;
}

/**
 *
 * @param dest
 * @param min
 * @return
 */
vector<int> Graph::getMinPath(int dest, int min) const {
    vector<int> path(min + 1);
    int current = dest;
    int i = min;
    path[i--] = current;
    while (i >= 0) {
        path[i--] = nodes[current].previous;
        current = nodes[current].previous;
    }
    return path;
}

/**
 *
 * @param airportCode
 */
void Graph::addNode(const std::string &airportCode) {
    n += 1;
    nodes.push_back({airportCode, {}, false, INT_MAX, 0, 0, 0, false});
}

/**
 *
 * @param source
 * @param target
 * @param airlineCode
 */
void Graph::addEdge(int source, int target, const std::string &airlineCode) {
    if (source < 1 || source > n || target < 1 || target > n)
        return;
    nodes[source].adj.push_back({target, airlineCode});
}

/**
 *
 */
void Graph::unvisitNodes() {
    for (int v = 1; v <= n; v++) {
        nodes[v].visited = false;
        nodes[v].distance = INT_MAX;
        nodes[v].previous = 0;
        nodes[v].num = 0;
        nodes[v].low = 0;
        nodes[v].inStack = false;
    }
}

void Graph::bfs(int v) {
    unvisitNodes();
    queue<int> q;
    q.push(v);
    nodes[v].visited = true;
    nodes[v].distance = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const Edge &edge : nodes[u].adj) {
            int w = edge.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
            }
        }
    }
}

/**
 *
 * @param sources
 * @param targets
 * @param filter
 */
void Graph::bfs_flights(const unordered_set<int> &sources, const unordered_set<int> &targets, const unordered_set<std::string> &filter) {
    unvisitNodes();
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
            if (filter.empty() || filter.find(edge.airlineCode) != filter.end()) {
                int w = edge.dest;
                if (!nodes[w].visited) {
                    q.push(w);
                    nodes[w].visited = true;
                    nodes[w].distance = nodes[u].distance + 1;
                    nodes[w].previous = u;
                }
                if (targets.find(edge.dest) != targets.end())
                    return;
            }
        }
    }
}
/**
 *
 * @param v
 */
void Graph::dfs(int v) {
    nodes[v].visited = true;
    for (const Edge &edge : nodes[v].adj) {
        int w = edge.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

/**
 *
 * @param v
 * @param isRoot
 * @param index
 * @param points
 */
void Graph::dfs_art(int v, bool isRoot, int &index, unordered_set<string> &points) {
    nodes[v].num = index;
    nodes[v].low = index;
    index++;
    nodes[v].inStack = true;
    int rootChilds = 0;
    for (const Edge &edge : nodes[v].adj) {
        int w = edge.dest;
        if (nodes[w].num == 0) {
            if (isRoot)
                rootChilds++;
            dfs_art(w, false, index, points);
            nodes[v].low = min(nodes[v].low, nodes[w].low);
            if ((!isRoot && nodes[w].low >= nodes[v].num) || (isRoot && rootChilds > 1))
                points.insert(nodes[v].airportCode);
        } else if (nodes[w].inStack)
            nodes[v].low = min(nodes[v].low, nodes[w].num);
    }
    nodes[v].inStack = false;
}

void Graph::dfs_scc(int v, int &index, int &scc) {
    nodes[v].num = index;
    nodes[v].low = index;
    index++;
    nodes[v].inStack = true;
    for (const Edge &edge : nodes[v].adj) {
        int w = edge.dest;
        if (nodes[w].num == 0) {
            dfs_scc(w, index, scc);
            nodes[v].low = min(nodes[v].low, nodes[w].low);
        } else if (nodes[w].inStack)
            nodes[v].low = min(nodes[v].low, nodes[w].num);
    }
    if (nodes[v].num == nodes[v].low)
        scc++;
    nodes[v].inStack = false;
}