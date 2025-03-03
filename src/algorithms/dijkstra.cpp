#include <vector>
#include <queue>
#include <limits>
#include <stdexcept>
#include "graph.hpp"

namespace graph {

template <typename T>
class Dijkstra {
public:
    Dijkstra(const AdjacencyListGraph<T>& graph, int source)
        : graph_(graph), source_(source) {}

    struct Result {
        std::vector<int32_t> distances;
    };

    Result run(int start) {
        std::vector<int32_t> distances(graph_.numberVertices(), std::numeric_limits<int32_t>::max());
        distances[start] = 0;
        
        auto comp = [&distances](int left, int right) { return distances[left] > distances[right]; };
        std::priority_queue<int, std::vector<int>, decltype(comp)> pq(comp);
        pq.push(start);

        while (!pq.empty()) {
            int vertex = pq.top();
            pq.pop();

            for (auto& edge : graph_.getNeighbours(vertex)) {
                int neighbor = edge.to();
                int newDist = distances[vertex] + edge.weight();
                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    pq.push(neighbor);
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
