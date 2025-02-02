#ifndef BFS_1K_HPP
#define BFS_1K_HPP

#include <limits>
#include <queue>

#include "graph.hpp"

namespace graph {

template <typename edgeType>
class BFS_1k {
public:
    BFS_1k(AdjacencyListGraph<edgeType>& graph, std::int32_t maxWeight)
        : m_graph(graph), m_maxWeight(maxWeight) {}

    class BFSResult {
    public:
        BFSResult(const std::vector<std::int32_t>& distances,
                  const std::vector<std::int32_t>& accessibility)
            : m_distances(distances), m_accessibility(accessibility) {}

        [[nodiscard]] const std::vector<std::int32_t>& distances() const { return m_distances; }

        [[nodiscard]] const std::vector<std::int32_t>& accessibility() const {
            return m_accessibility;
        }

    private:
        std::vector<std::int32_t> m_distances;
        std::vector<std::int32_t> m_accessibility;
    };

    // Метод для запуска алгоритма 1-k BFS
    BFSResult run(std::int32_t startVertex);

private:
    AdjacencyListGraph<edgeType>& m_graph;
    std::int32_t m_maxWeight;
};

template <typename edgeType>
BFS_1k(AdjacencyListGraph<Edge<edgeType>>&, int, int) -> BFS_1k<edgeType>;

template <typename edgeType>
typename BFS_1k<edgeType>::BFSResult BFS_1k<edgeType>::run(std::int32_t startVertex) {
    std::vector<std::int32_t> distances(m_graph.numberVertices(),
                                        std::numeric_limits<std::int32_t>::max());
    std::vector<std::int32_t> reachability(m_graph.numberVertices());
    distances[startVertex] = 0;

    std::queue<std::int32_t> queues[m_maxWeight + 1];
    queues[0].push(startVertex);

    std::int32_t numberOfVerticesInQueues = 1, currentDistance = 0;
    while (numberOfVerticesInQueues) {
        while (queues[currentDistance % (m_maxWeight + 1)].empty()) {
            currentDistance++;
        }

        std::int32_t currentVertex = queues[currentDistance % (m_maxWeight + 1)].front();
        queues[currentDistance % (m_maxWeight + 1)].pop();
        --numberOfVerticesInQueues;

        if (reachability[currentVertex]) {
            continue;  // Если расстояние уже было посчитано
        }
        reachability[currentVertex] = true;

        auto neighbours = m_graph.getNeighbours(currentVertex);
        for (const auto& edge : neighbours) {
            std::int32_t newDistance = currentDistance + edge.edge();
            if (newDistance < distances[edge.to()]) {
                distances[edge.to()] = newDistance;
                queues[newDistance % (m_maxWeight + 1)].push(edge.to());
                ++numberOfVerticesInQueues;
            }
        }
    }

    return BFSResult{distances, reachability};
}

};  // namespace graph

#endif  // BFS_1K_HPP