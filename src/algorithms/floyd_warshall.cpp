#include <vector>
#include <limits>
#include <stdexcept>
#include "graph.hpp"

namespace graph {

template <typename T>
class FloydWarshall {
public:
    FloydWarshall(const AdjacencyListGraph<T>& graph)
        : graph_(graph) {}

    struct Result {
        std::vector<std::vector<int32_t>> distances;
    };

    Result run() {
        int V = graph_.numberVertices();
        std::vector<std::vector<int32_t>> dist(V, std::vector<int32_t>(V, std::numeric_limits<int32_t>::max()));

        for (int u = 0; u < V; ++u) {
            dist[u][u] = 0;
        }

        for (int u = 0; u < V; ++u) {
            for (auto& edge : graph_.getNeighbours(u)) {
                int v = edge.to();
                int weight = edge.weight();
                dist[u][v] = weight;
            }
        }

        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    if (dist[i][k] != std::numeric_limits<int32_t>::max() &&
                        dist[k][j] != std::numeric_limits<int32_t>::max() &&
                        dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        return {dist};
    }

private:
    const AdjacencyListGraph<T>& graph_;
};

}
