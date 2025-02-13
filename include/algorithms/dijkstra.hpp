#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <limits>
#include <queue>

#include "graph.hpp"

namespace graph {

template <typename edgeType>
class Dijkstra {
public:
    explicit Dijkstra(Graph<edgeType>& graph) : m_graph(graph) {}

    class DijkstraResult {
    public:
        explicit DijkstraResult(const std::vector<std::int64_t>& distances) : m_distances(distances) {}

        [[nodiscard]] const std::vector<std::int64_t>& distances() const { return m_distances; }
    private:
        std::vector<std::int64_t> m_distances;
    };

    DijkstraResult runStandard(std::int32_t start);

    DijkstraResult runOptimized(std::int32_t start);

private:
    Graph<edgeType>& m_graph;
};

template <typename edgeType>
typename Dijkstra<edgeType>::DijkstraResult Dijkstra<edgeType>::runStandard(std::int32_t start) {
    std::vector<std::int64_t> distances(m_graph.numberVertices(),
                                        std::numeric_limits<std::int64_t>::max());
    std::vector<bool> visited(m_graph.numberVertices(), false);

    distances[start] = 0;

    for (std::int32_t iteration = 0; iteration < m_graph.numberVertices(); iteration++) {
        std::int32_t currentMinimumVertex = -1;
        for (std::int32_t currentVertex = 0; currentVertex < m_graph.numberVertices();
             currentVertex++) {
            if (!visited[currentVertex] &&
                (currentMinimumVertex == -1 ||
                 distances[currentVertex] < distances[currentMinimumVertex])) {
                currentMinimumVertex = currentVertex;
            }
        }

        if (distances[currentMinimumVertex] == std::numeric_limits<std::int64_t>::max()) {
            break;
        }

        visited[currentMinimumVertex] = true;

        std::vector<Edge<edgeType>> neighbours;
        m_graph.getNeighbours(currentMinimumVertex, neighbours);
        for (const auto& edge : neighbours) {
            std::int64_t newDistance = distances[currentMinimumVertex] + edge.edge();
            if (newDistance < distances[edge.to()]) {
                distances[edge.to()] = newDistance;
            }
        }
    }

    return DijkstraResult{distances};
}

template <typename edgeType>
typename Dijkstra<edgeType>::DijkstraResult Dijkstra<edgeType>::runOptimized(std::int32_t start) {
    std::vector<std::int64_t> distances(m_graph.numberVertices(),
                                        std::numeric_limits<std::int64_t>::max());
    std::vector<bool> visited(m_graph.numberVertices(), false);

    struct QueueNode {
        std::int64_t distance;
        std::int32_t vertex;

        bool operator>(const QueueNode& other) const {
            return distance > other.distance;
        }
    };

    distances[start] = 0;
    std::priority_queue<QueueNode, std::vector<QueueNode>, std::greater<QueueNode>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        std::int32_t currentVertex = pq.top().vertex;
        pq.pop();

        if (visited[currentVertex]) {
            continue;
        }
        visited[currentVertex] = true;

        std::vector<Edge<edgeType>> neighbours;
        m_graph.getNeighbours(currentVertex, neighbours);
        for (const auto& edge : neighbours) {
            std::int32_t to = edge.to();
            edgeType weight = edge.edge();

            if (distances[currentVertex] + weight < distances[to]) {
                distances[to] = distances[currentVertex] + weight;
                pq.push({distances[to], to});
            }
        }
    }

    return DijkstraResult{distances};
}

}  // namespace graph

#endif