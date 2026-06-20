#include<bits/stdc++.h>
using namespace std;

class Graph {
    int numVertices;
    vector<list<pair<int, int>>> adjList; 

public:
    Graph(int vertices) {
        numVertices = vertices;
        adjList.resize(vertices);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back(make_pair(v, weight));
        adjList[v].push_back(make_pair(u, weight));
    }

    void dijkstra(int startNode) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> distances(numVertices, 1e9); // 1e9 represents infinity

        pq.push(make_pair(0, startNode));
        distances[startNode] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    pq.push(make_pair(distances[v], v));
                }
            }
        }
        
        cout << "Shortest distances from Node " << startNode << ":\n";
        for (int i = 0; i < numVertices; ++i) {
            cout << "Node " << i << " \t Distance: " << distances[i] << "\n";
        }
    }
};

int main() {
    Graph cityMap(5); 
    
    // Adding some roads (edges) between locations (nodes) with distances (weights)
    cityMap.addEdge(0, 1, 9);
    cityMap.addEdge(0, 2, 6);
    cityMap.addEdge(1, 2, 2);
    cityMap.addEdge(1, 3, 4);
    cityMap.addEdge(2, 3, 1);
    cityMap.addEdge(3, 4, 3);

    cout << "Calculating optimal routes...\n";
    cityMap.dijkstra(0); // Find shortest paths from Node 0
    
    return 0;
}