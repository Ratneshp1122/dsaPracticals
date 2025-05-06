#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {
    int vertices;
    vector<vector<int>> adjMatrix;
    vector<vector<int>> adjList;

public:
    Graph(int v) : vertices(v) {
        adjMatrix.resize(v, vector<int>(v, 0));
        adjList.resize(v);
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printMatrix() {
        cout << "\nAdjacency Matrix:\n";
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++)
                cout << adjMatrix[i][j] << " ";
            cout << endl;
        }
    }

    void printList() {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < vertices; i++) {
            cout << i << " -> ";
            for (int neighbor : adjList[i])
                cout << neighbor << " ";
            cout << endl;
        }
    }

    void DFS_matrix(int start) {
        vector<bool> visited(vertices, false);
        stack<int> s;
        s.push(start);

        cout << "\nDFS (Matrix) from node " << start << ":\n";
        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                cout << node << " ";
                visited[node] = true;

                for (int i = vertices - 1; i >= 0; i--)
                    if (adjMatrix[node][i] && !visited[i])
                        s.push(i);
            }
        }
        cout << endl;
    }

    void BFS_matrix(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "\nBFS (Matrix) from node " << start << ":\n";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int i = 0; i < vertices; i++) {
                if (adjMatrix[node][i] && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }

    void DFS_list(int start) {
        vector<bool> visited(vertices, false);
        stack<int> s;
        s.push(start);

        cout << "\nDFS (List) from node " << start << ":\n";
        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                cout << node << " ";
                visited[node] = true;

                for (int i = adjList[node].size() - 1; i >= 0; i--) {
                    int neighbor = adjList[node][i];
                    if (!visited[neighbor])
                        s.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void BFS_list(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "\nBFS (List) from node " << start << ":\n";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int v, e, u, v1, choice, start;

    cout << "Enter number of vertices: ";
    cin >> v;

    Graph g(v);

    cout << "Enter number of edges: ";
    cin >> e;
    cout << "Enter " << e << " edges (u v):\n";
    for (int i = 0; i < e; i++) {
        cin >> u >> v1;
        g.addEdge(u, v1);
    }

    g.printMatrix();
    g.printList();

    cout << "\nTraversal Options:\n";
    cout << "1. DFS using Matrix\n";
    cout << "2. BFS using Matrix\n";
    cout << "3. DFS using List\n";
    cout << "4. BFS using List\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cout << "Enter starting node: ";
    cin >> start;

    switch (choice) {
        case 1: g.DFS_matrix(start); break;
        case 2: g.BFS_matrix(start); break;
        case 3: g.DFS_list(start); break;
        case 4: g.BFS_list(start); break;
        default: cout << "Invalid choice. Are you trying to BFS into the void?" << endl;
    }

    return 0;
}
