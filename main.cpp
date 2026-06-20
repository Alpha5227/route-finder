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

    void dijkstra(int startNode, int endNode) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> distances(numVertices, 1e9); 
        vector<int> parent(numVertices, -1); // Array to track the path

        pq.push(make_pair(0, startNode));
        distances[startNode] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            // Optimization: Stop if we reached the destination
            if (u == endNode) break; 

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    parent[v] = u; // Record how we got to this node
                    pq.push(make_pair(distances[v], v));
                }
            }
        }
        
        if (distances[endNode] == 1e9) {
            cout << "\nNo path exists between " << startNode << " and " << endNode << ".\n";
            return;
        }

        cout << "\n--- Route Found! ---\n";
        cout << "Total Distance: " << distances[endNode] << "\n";
        cout << "Optimal Path: ";
        
        // Backtrack from endNode to startNode to build the path
        vector<int> path;
        for (int curr = endNode; curr != -1; curr = parent[curr]) {
            path.push_back(curr);
        }
        reverse(path.begin(), path.end());
        
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << "\n";
    }
};

int main() {
    int nodes, edges;
    cout << "Welcome to the Interactive Route Finder!\n";
    cout << "Enter total number of locations (nodes): ";
    cin >> nodes;
    
    Graph cityMap(nodes);
    
    cout << "Enter total number of roads (edges): ";
    cin >> edges;
    
    cout << "Define each road (Start Node, End Node, Distance/Weight).\n";
    cout << "Example input format: '0 1 5'\n";
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cout << "Road " << i + 1 << ": ";
        cin >> u >> v >> w;
        cityMap.addEdge(u, v, w);
    }
    
    int start, end;
    cout << "\nEnter your starting location: ";
    cin >> start;
    cout << "Enter your destination: ";
    cin >> end;
    
    cityMap.dijkstra(start, end);
    
    return 0;
}