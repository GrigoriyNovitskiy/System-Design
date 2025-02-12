#ifndef FLOYD_WARSHALL_HPP
#define FLOYD_WARSHALL_HPP

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>

#include "graph.hpp"

namespace graph {

template <typename edgeType>
class FloydWarshall {
public:
    FloydWarshall(Graph<edgeType>& graph) : m_graph(graph) {}

    class FloydWarshallResult {
    public:
        FloydWarshallResult(const std::vector<std::vector<std::int32_t>>& distances,
                            bool has_negative_cycles)
            : m_distances(distances), m_has_negative_cycles(has_negative_cycles) {}

        [[nodiscard]] const std::vector<std::vector<std::int32_t>>& distances() const {
            return m_distances;
        }

        [[nodiscard]] const bool has_negative_cycles() const { return m_has_negative_cycles; }

    private:
        std::vector<std::vector<std::int32_t>> m_distances;
        bool m_has_negative_cycles;
    };

    // Метод для запуска алгоритма Флойда-Уоршелла
    FloydWarshallResult run();

private:
    Graph<edgeType>& m_graph;
};

template <typename edgeType>
FloydWarshall(AdjacencyMatrixGraph<Edge<edgeType>>&, int, int) -> FloydWarshall<edgeType>;

template <typename edgeType>
typename FloydWarshall<edgeType>::FloydWarshallResult FloydWarshall<edgeType>::run() {
    std::vector<std::vector<std::int32_t>> distances(
        m_graph.numberVertices(),
        std::vector<std::int32_t>(m_graph.numberVertices(),
                                  std::numeric_limits<std::int32_t>::max()));

    for (int vertex = 0; vertex < m_graph.numberVertices(); vertex++) {
        distances[vertex][vertex] = 0;

        std::vector<Edge<edgeType>> neighbours;
        m_graph.getNeighbours(vertex, neighbours);
        for (const auto& edge : neighbours) {
            distances[vertex][edge.to()] = std::min(distances[vertex][edge.to()], edge.edge());
        }
    }

    for (int mid_vertex = 0; mid_vertex < m_graph.numberVertices(); mid_vertex++) {
        for (int begin_vertex = 0; begin_vertex < m_graph.numberVertices(); begin_vertex++) {
            for (int end_vertex = 0; end_vertex < m_graph.numberVertices(); end_vertex++) {
                if (distances[begin_vertex][mid_vertex] !=
                        std::numeric_limits<std::int32_t>::max() &&
                    distances[mid_vertex][end_vertex] != std::numeric_limits<std::int32_t>::max()) {
                    distances[begin_vertex][end_vertex] = std::min(
                        distances[begin_vertex][end_vertex],
                        distances[begin_vertex][mid_vertex] + distances[mid_vertex][end_vertex]);
                }
            }
        }
    }

    bool has_negative_cycles = false;

    for (int vertex = 0; vertex < m_graph.numberVertices(); vertex++) {
        has_negative_cycles |= (distances[vertex][vertex] != 0);
    }

    return FloydWarshallResult{distances, has_negative_cycles};
}

};  // namespace graph

#endif  // FLOYD_WARSHALL_HPP