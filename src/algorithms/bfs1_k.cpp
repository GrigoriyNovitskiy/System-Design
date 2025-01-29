#include <limits>
#include <queue>
#include "bfs1_k.hpp"

BFS_1k::BFS_1k(AdjacencyListGraph &graph, std::int32_t startVertex, std::int32_t maxWeight)
    : m_graph(graph), m_startVertex(startVertex), m_maxWeight(maxWeight) {}

std::vector<std::int32_t> BFS_1k::run() {
    std::vector<std::int32_t> distances(m_graph.numVertices(), std::numeric_limits<std::int32_t>::max());
    std::vector<std::int32_t> was(m_graph.numVertices());
    distances[m_startVertex] = 0;

    std::queue<std::int32_t> queues[m_maxWeight + 1];
    queues[0].push(m_startVertex);

    std::int32_t numberOfVerticesInQueues = 1, currentDistance = 0;
    while (numberOfVerticesInQueues) {
        while (queues[currentDistance % (m_maxWeight + 1)].empty()) {
            currentDistance++;
        }

        std::int32_t currentVertex = queues[currentDistance].front();
        queues[currentDistance].pop();
        --numberOfVerticesInQueues;

        if (was[currentVertex]) {
            continue; // Если расстояние уже было посчитано
        }
        was[currentVertex] = true;

        for (const auto& edge : m_graph.getAdjList()[currentVertex]) {
            std::int32_t newDistance = currentDistance + edge.weight();
            if (newDistance < distances[edge.to()]) {
                distances[edge.to()] = newDistance;
                queues[newDistance % (m_maxWeight + 1)].push(edge.to());
                ++numberOfVerticesInQueues;
            }
        }

    }

    return distances;
}
