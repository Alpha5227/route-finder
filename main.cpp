#include<bits/stdc++.h>
using namespace std;

class Graph {
    int numVertices;
    // Adjacency list: stores pairs of (destination node, weight/distance)
    vector<list<pair<int, int>>> adjList; 

public:
    Graph(int vertices) {
        numVertices = vertices;
        adjList.resize(vertices);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back(make_pair(v, weight));
        adjList[v].push_back(make_pair(u, weight)); // Assuming a two-way street
    }
};

int main() {
    cout << "Route Finder Initialized!" << endl;
    cout << "Graph structure ready. Dijkstra's algorithm pending..." << endl;
    
    Graph cityMap(5); // Initializing a map with 5 locations
    
    return 0;
}