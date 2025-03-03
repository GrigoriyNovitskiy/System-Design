#include <vector>
#include <limits>
#include <stdexcept>
#include "graph.hpp"

namespace graph {

template <typename T>
class BellmanFord {
public:
    BellmanFord(const AdjacencyListGraph<T>& graph, int source)
        : graph_(graph), source_(source) {}

    struct Result {
        std::vector<int32_t> distances;
    };

    Result run(int start) {
        int V = graph_.numberVertices();
        std::vector<int32_t> distances(V, std::numeric_limits<int32_t>::max());
        distances[start] = 0;

        for (int i = 1; i < V; ++i) {
            for (int u = 0; u < V; ++u) {
                for (auto& edge : graph_.getNeighbours(u)) {
                    int v = edge.to();
                    int weight = edge.weight();
                    if (distances[u] != std::numeric_limits<int32_t>::max() && distances[u] + weight < distances[v]) {
                        distances[v] = distances[u] + weight;
                    }
                }
            }
        }

        for (int u = 0; u < V; ++u) {
            for (auto& edge : graph_.getNeighbours(u)) {
                int v = edge.to();
                int weight = edge.weight();
                if (distances[u] != std::numeric_limits<int32_t>::max() && distances[u] + weight < distances[v]) {
                    throw std::runtime_error("Graph contains negative weight cycle");
                }
            }
        }

        return {distances};
    }

private:
    const AdjacencyListGraph<T>& graph_;
    int source_;
};

}
