#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Class representing an edge in the graph
class Edge {
public:
    int src, dest;
    double weight;
};

// Class representing a connected, directed, and weighted graph
class Graph {
public:
    int V, E;
    vector<Edge> edge;
};

// Function to create a graph with V vertices and E edges
Graph createGraph(int V, int E) {
    Graph graph;
    graph.V = V;
    graph.E = E;
    graph.edge.resize(E);
    return graph;
}

// Function to check if there is a negative weight cycle using the Bellman-Ford algorithm
bool isNegCycleBellmanFord(Graph graph, int src) {
    int V = graph.V;
    int E = graph.E;
    vector<double> dist(V, 0);

    dist[src] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph.edge[j].src;
            int v = graph.edge[j].dest;
            double weight = graph.edge[j].weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = graph.edge[i].src;
        int v = graph.edge[i].dest;
        double weight = graph.edge[i].weight;

        if (dist[u] + weight < dist[v]) {
            return true;
        }
    }

    return false;
}

int main() {
    int n, m;
    cin >> n;
    cin >> m;

    Graph graph = createGraph(n, m);

    for (int i = 0; i < m; i++) {
        double u, v, w;
        cin >> u >> v >> w;
        graph.edge[i].src = static_cast<int>(u);
        graph.edge[i].dest = static_cast<int>(v);
        graph.edge[i].weight = -log(w);
    }

    if (isNegCycleBellmanFord(graph, 0)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}
