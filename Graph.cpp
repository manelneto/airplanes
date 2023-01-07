//
// Created by manue on 30/12/2022.
//

#include "Graph.h"
#include <queue>

using namespace std;

/**Construtor com parâmetro. Constrói um grafo com n vértices.
 * <br>Complexidade Temporal: O(n), sendo n o número de vértices mais um.
 * @param n número de vértices
 */
Graph::Graph(int n) : n(n), nodes(n + 1) {}

/**Retorna o número de vértices do grafo.
 * <br>Complexidade Temporal: O(1)
 * @return número de vértices do grafo
 */
int Graph::getN() const {
    return n;
}

/**Retorna os vértices do grafo.
 * <br>Complexidade Temporal: O(1)
 * @return vértices do grafo.
 */
const vector<Node> &Graph::getNodes() const {
    return nodes;
}

/**Retorna os códigos ICAO das companhias áereas que fazem o voo do nó src para o nó dest, filtrando-os de acordo com filter.
 * <br>Complexidade Temporal: O(n), sendo n o tamanho da lista de adjacências do nó src
 * @param src nó de origem
 * @param dest nó de destino
 * @param filter se não vazio, filtro de companhias aéreas a incluir
 * @return códigos ICAO das companhias áereas que fazem o voo do nó src para o nó dest, filtrados de acordo com filter
 */
vector<string> Graph::getAirlinesCodes(int src, int dest, const unordered_set<string> &filter) const {
    vector<string> airlinesCodes;
    for (const Edge &edge : nodes[src].adj)
        if (edge.dest == dest && (filter.empty() || filter.find(edge.airlineCode) != filter.end()))
            airlinesCodes.push_back(edge.airlineCode);
    return airlinesCodes;
}

/**Retorna os nós do caminho de comprimento min até ao nó dest. Só faz sentido ser chamada depois de uma BFS que calcule as distâncias de cada nó aos nós de origem da BFS.
 * <br>Complexidade Temporal: O(n), sendo n = min
 * @param dest nó de destino do caminho
 * @param min comprimento do caminho
 * @return nós do caminho de comprimento min até ao nó dest
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

/**Adiciona ao grafo um nó com airportCode passado pelo parâmetro homónimo (sem mais informação e sem arestas).
 * <br>Complexidade Temporal: O(1)
 * @param airportCode código IATA do aeroporto a atribuir ao nó
 */
void Graph::addNode(const std::string &airportCode) {
    n += 1;
    nodes.push_back({airportCode, {}, false, INT_MAX, 0, 0, 0, false});
}

/**Adiciona ao grafo uma aresta dirigida do nó source para o nó target e com airlineCode passado pelo parâmetro homónimo.
 * <br>Complexidade Temporal: O(1)
 * @param source nó de origem da aresta
 * @param target nó de destino da aresta
 * @param airlineCode código ICAO da companhia aérea a atribuir à aresta
 */
void Graph::addEdge(int source, int target, const std::string &airlineCode) {
    if (source < 1 || source > n || target < 1 || target > n)
        return;
    nodes[source].adj.push_back({target, airlineCode});
}

/**Define todos os nós como não visitados, anulando os valores anteriores dos seus atributos.
 * <br>Complexidade Temporal: O(n)
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

/**Pesquisa em Largura a partir do nó v, calculando a distância de cada nó ao nó v.
 * <br>Complexidade Temporal: O(|V| + |E|), sendo V o número de vértices do grafo e E o número de arestas do grafo
 * @param v nó de origem da Pesquisa em Largura
 */
void Graph::bfs_distance(int v) {
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

/**Pesquisa em Largura a partir dos nós em sources até aos nós em targets (se alcançáveis), atravessando apenas as arestas cujo código está em filter (se não vazio), calculando a distância de cada nó aos nós de origem e o seu antecessor na Pesquisa em Largura.
 * <br>Complexidade Temporal: O(|V| + |E|), sendo V o número de vértices do grafo e E o número de arestas do grafo
 * @param sources nós de origem da Pesquisa em Largura
 * @param targets nós de destino da Pesquisa em Largura
 * @param filter se não vazio, filtro dos códigos das arestas a atravessar
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

/**Pesquisa em Profunidade a partir do nó v, encontrando os pontos de articulação do grafo de acordo com algoritmo semelhante ao de Tarjan.
 * <br>Complexidade Temporal: O(|V| + |E|), sendo V o número de vértices do grafo e E o número de arestas do grafo
 * @param v nó de origem da Pesquisa em Profundidade
 * @param isRoot true se o nó de origem é uma raiz da árvore de DFS, false caso contrário
 * @param index índice da Pesquisa em Profundidade para o algoritmo de Tarjan
 * @param points pontos de articulação encontrados
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

/**Pesquisa em Profunidade a partir do nó v, encontrando o número de componentes fortemente conexos do grafo de acordo com algoritmo de Tarjan.
 * <br>Complexidade Temporal: O(|V| + |E|), sendo V o número de vértices do grafo e E o número de arestas do grafo
 * @param v nó de origem da Pesquisa em Profundidade
 * @param index índice da Pesquisa em Profundidade para o algoritmo de Tarjan
 * @param s pilha de nós para o algoritmo de Tarjan
 * @param scc número de componentes fortemente conexos encontrados
 */
void Graph::dfs_scc(int v, int &index, stack<int> &s, int &scc) {
    nodes[v].num = index;
    nodes[v].low = index;
    index++;
    nodes[v].inStack = true;
    s.push(v);
    for (const Edge &edge : nodes[v].adj) {
        int w = edge.dest;
        if (nodes[w].num == 0) {
            dfs_scc(w, index, s, scc);
            nodes[v].low = min(nodes[v].low, nodes[w].low);
        } else if (nodes[w].inStack)
            nodes[v].low = min(nodes[v].low, nodes[w].num);
    }
    if (nodes[v].num == nodes[v].low) {
        scc++;
        while (true) {
            int w = s.top();
            s.pop();
            nodes[w].inStack = false;
            if (w == v)
                break;
        }
    }
}

/**Calcula e retorna o diâmetro do grafo.
 * <br>Complexidade Temporal: O(|V| * (2|V| + |E|)), sendo V o número de vértices do grafo flights e E o número de arestas do grafo
 * @return diâmetro do grafo
 */
unsigned Graph::diameter() {
    unsigned diametro = 0;
    for (int v = 1; v <= n; v++) {
        bfs_distance(v);
        for (int u = 1; u <= n; u++)
            if (nodes[u].visited && nodes[u].distance > diametro)
                diametro = nodes[u].distance;
    }
    return diametro;
}
