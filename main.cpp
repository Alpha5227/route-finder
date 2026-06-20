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
        vector<int> parent(numVertices, -1); 

        pq.push(make_pair(0, startNode));
        distances[startNode] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (u == endNode) break; 

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    parent[v] = u; 
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
        
        vector<int> path;
        for (int curr = endNode; curr != -1; curr = parent[curr]) {
            path.push_back(curr);
        }
        reverse(path.begin(), path.end());
        
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << "\n\n";
    }
};

int main() {
    cout << "Initializing Routing Engine...\n";
    
    // We initialize the graph with 8 nodes (0 through 7) based on our CSV data
    Graph cityMap(8);
    
    // --- FILE PARSING LOGIC ---
    ifstream mapFile("city_map.csv");
    string line;
    
    if (!mapFile.is_open()) {
        cout << "Error: Could not open city_map.csv. Make sure it is in the same folder!\n";
        return 1;
    }

    // Read and ignore the first header line ("StartNode,EndNode,Distance")
    getline(mapFile, line); 

    int roadCount = 0;
    // Read the file line by line
    while (getline(mapFile, line)) {
        stringstream ss(line);
        string u_str, v_str, w_str;
        
        // Split the line by commas
        getline(ss, u_str, ',');
        getline(ss, v_str, ',');
        getline(ss, w_str, ',');
        
        // Convert strings to integers and add the edge
        cityMap.addEdge(stoi(u_str), stoi(v_str), stoi(w_str));
        roadCount++;
    }
    mapFile.close();
    
    cout << "Successfully loaded " << roadCount << " roads from database.\n";
    // --------------------------

    int start, end;
    cout << "\nEnter your starting node (0-7): ";
    cin >> start;
    cout << "Enter your destination node (0-7): ";
    cin >> end;
    
    cityMap.dijkstra(start, end);
    
    return 0;
}