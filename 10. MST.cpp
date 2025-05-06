#include <iostream>
#include <vector>

using namespace std;

const int INF = 999999; // substitute for INT_MAX

struct Edge {
    int u, v, w;
};

void sortEdges(vector<Edge>& edges) {
    // Bubble sort (avoid algorithm header)
    for (int i = 0; i < edges.size(); i++) {
        for (int j = 0; j < edges.size() - i - 1; j++) {
            if (edges[j].w > edges[j + 1].w) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int find(int parent[], int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent, parent[i]);
}

void unionSet(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

void displayMatrix(vector<vector<int>>& matrix) {
    cout << "\nAdjacency Matrix:\n";
    for (auto& row : matrix) {
        for (int val : row)
            cout << (val == INF ? -1 : val) << "\t";
        cout << "\n";
    }
}

void displayList(vector<vector<pair<int, int>>>& adjList) {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < adjList.size(); i++) {
        cout << i << " -> ";
        for (auto& p : adjList[i])
            cout << "(" << p.first << "," << p.second << ") ";
        cout << "\n";
    }
}

void prim(vector<vector<int>>& matrix) {
    int V = matrix.size();
    vector<int> key(V, INF);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);
    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min = INF, u = -1;
        for (int i = 0; i < V; i++)
            if (!inMST[i] && key[i] < min)
                min = key[i], u = i;

        inMST[u] = true;

        for (int v = 0; v < V; v++)
            if (matrix[u][v] && !inMST[v] && matrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = matrix[u][v];
            }
    }

    cout << "\nPrim's MST:\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " : " << matrix[i][parent[i]] << "\n";
}

void kruskal(vector<Edge>& edges, int V) {
    int* parent = new int[V];
    int* rank = new int[V];
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    sortEdges(edges);

    cout << "\nKruskal's MST:\n";
    int count = 0;
    for (auto& e : edges) {
        int u = e.u;
        int v = e.v;
        int setU = find(parent, u);
        int setV = find(parent, v);

        if (setU != setV) {
            cout << u << " - " << v << " : " << e.w << "\n";
            unionSet(parent, rank, setU, setV);
            count++;
        }
        if (count == V - 1) break;
    }

    delete[] parent;
    delete[] rank;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> matrix(V, vector<int>(V, INF));
    vector<vector<pair<int, int>>> adjList(V);
    vector<Edge> edges;

    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        matrix[u][v] = matrix[v][u] = w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
        edges.push_back({u, v, w});
    }

    displayMatrix(matrix);
    displayList(adjList);

    cout << "\nChoose algorithm:\n1. Prim's\n2. Kruskal's\nChoice: ";
    int choice;
    cin >> choice;

    if (choice == 1)
        prim(matrix);
    else if (choice == 2)
        kruskal(edges, V);
    else
        cout << "Invalid choice.\n";

    return 0;
}

