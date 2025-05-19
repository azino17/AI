#include <iostream>
#include <vector>
using namespace std;

// Function to check if a color can be assigned to a vertex
bool isSafe(int v, vector<vector<int>>& graph, vector<int>& colors, int c) {
    for (int i = 0; i < graph.size(); i++) {
        if (graph[v][i] == 1 && colors[i] == c) {
            return false; // Adjacent vertex has the same color
        }
    }
    return true;
}

// CSP-based function for Graph Coloring using Backtracking
bool graphColoringCSP(vector<vector<int>>& graph, int m, vector<int>& colors, int v) {
    if (v == graph.size()) {
        return true; // All vertices are colored
    }

    for (int c = 1; c <= m; c++) {
        cout << "Trying color " << c << " for vertex " << v + 1 << "...\n";
        if (isSafe(v, graph, colors, c)) {
            colors[v] = c;
            cout << "Assigned color " << c << " to vertex " << v + 1 << "\n";

            if (graphColoringCSP(graph, m, colors, v + 1)) {
                return true;
            }

            // Backtrack
            cout << "Backtracking from vertex " << v + 1 << " color " << c << "\n";
            colors[v] = 0;
        } else {
            cout << "Color " << c << " not safe for vertex " << v + 1 << "\n";
        }
    }

    return false;
}

// Function to start Graph Coloring
void solveGraphColoring(vector<vector<int>>& graph, int m) {
    int n = graph.size();
    vector<int> colors(n, 0);

    if (graphColoringCSP(graph, m, colors, 0)) {
        cout << "\n✅ Solution Exists with " << m << " colors:\n";
        for (int i = 0; i < n; i++) {
            cout << "Vertex " << i + 1 << " ---> Color " << colors[i] << endl;
        }
    } else {
        cout << "\n❌ No solution exists with " << m << " colors." << endl;
    }
}

int main() {
    int n, m;
    cout << "Enter the number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    cout << "Enter the adjacency matrix of the graph:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    cout << "Enter the number of colors: ";
    cin >> m;

    solveGraphColoring(graph, m);

    return 0;
}
