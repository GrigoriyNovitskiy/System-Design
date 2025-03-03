#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class BipartiteGraph {
public:
    BipartiteGraph(int U, int V) : U(U), V(V), adj(U), matchU(U, -1), matchV(V, -1), visited(U, false) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    int kuhn() {
        int result = 0;
        for (int u = 0; u < U; ++u) {
            visited.assign(U, false);
            if (dfs(u)) {
                result++;
            }
        }
        return result;
    }

private:
    int U, V;
    vector<vector<int>> adj;
    vector<int> matchU, matchV;
    vector<bool> visited;

    bool dfs(int u) {
        if (visited[u]) return false;
        visited[u] = true;
        for (int v : adj[u]) {
            if (matchV[v] == -1 || dfs(matchV[v])) {
                matchU[u] = v;
                matchV[v] = u;
                return true;
            }
        }
        return false;
    }
};
