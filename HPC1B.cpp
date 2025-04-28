#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>
using namespace std;

const int MAX = 100;
vector<int> graph[MAX];
bool visited[MAX];

void bfs(int start_node) {
    queue<int> q;
    q.push(start_node);
    visited[start_node] = true;

    while (!q.empty()) {
        int qSize = q.size();
        vector<int> nodesAtCurrentLevel;

        for (int i = 0; i < qSize; i++) {
            int curr = q.front();
            q.pop();
            nodesAtCurrentLevel.push_back(curr);
        }

        #pragma omp parallel for
        for (int i = 0; i < nodesAtCurrentLevel.size(); i++) {
            int u = nodesAtCurrentLevel[i];
            #pragma omp critical
            {
                cout << "\t" << u;
            }

            for (int v : graph[u]) {
                #pragma omp critical
                {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // undirected graph
    }

    for (int i = 0; i < n; i++) visited[i] = false;

    int start_node;
    cout << "Enter starting node: ";
    cin >> start_node;

    cout << "\nBFS Traversal:" << endl;
    bfs(start_node);

    return 0;
}
