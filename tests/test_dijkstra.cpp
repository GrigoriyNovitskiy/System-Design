#include "dijkstra.hpp"
#include "gtest/gtest.h"

TEST(DijkstraTest, BaseTestList1) {
    graph::AdjacencyListGraph<int> graph(4, false);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 1);

    graph::Dijkstra<int> dijkstra(graph);
    auto distances = dijkstra.runOptimized(0);
    std::vector<std::int64_t> correct_distances = {0, 3, 1, 2};
    ASSERT_EQ(distances.distances(), correct_distances);
}

TEST(DijkstraTest, BaseTestList2) {
    graph::AdjacencyListGraph<int> graph(4, false);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);

    graph::Dijkstra<int> dijkstra(graph);
    auto distances = dijkstra.runStandard(0);
    std::vector<std::int64_t> correct_distances = {0, 1, 1, 2};
    ASSERT_EQ(distances.distances(), correct_distances);
}

TEST(DijkstraTest, BaseTestList3) {
    graph::AdjacencyListGraph<int> graph(5, false);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 3);

    graph::Dijkstra<int> dijkstra(graph);
    auto distances = dijkstra.runOptimized(0);
    std::vector<std::int64_t> correct_distances = {0, 1, 3, 6,
                                                   std::numeric_limits<std::int64_t>::max()};
    ASSERT_EQ(distances.distances(), correct_distances);
}

// Тесты для AdjacencyMatrixGraph
TEST(DijkstraTest, BaseTestMatrix1) {
    graph::AdjacencyMatrixGraph<int> graph(5, false);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 3);

    graph::Dijkstra<int> dijkstra(graph);
    auto distances = dijkstra.runOptimized(0);
    std::vector<std::int64_t> correct_distances = {0, 1, 3, 6,
                                                   std::numeric_limits<std::int64_t>::max()};
    ASSERT_EQ(distances.distances(), correct_distances);
}

struct Edge {
    explicit Edge(std::int32_t weight, const std::string& label)
        : m_weight(weight), m_label(label) {}

    Edge operator+(const Edge& edge) const {
        return Edge(m_weight + edge.m_weight, m_label + edge.m_label);
    }

    [[nodiscard]] std::int32_t weight() const { return m_weight; }

    [[nodiscard]] std::string label() const { return m_label; }

private:
    std::int32_t m_weight;
    std::string m_label;

    friend std::ostream& operator<<(std::ostream& os, const Edge& e);
};

std::ostream& operator<<(std::ostream& os, const Edge& e) {
    os << "(" << e.m_weight << ", " << e.m_label << ")";
    return os;
}

std::int32_t operator+(std::int32_t value, const Edge& edge) { return value + edge.weight(); }

TEST(DijkstraTest, BaseTestCustomEdge1) {
    graph::AdjacencyMatrixGraph<Edge> graph(5, false);
    graph.addEdge(0, 1, Edge(1, "aaa"));
    graph.addEdge(1, 2, Edge(2, "bbb"));
    graph.addEdge(2, 3, Edge(3, "ccc"));

    graph::Dijkstra<Edge> dijkstra(graph);
    auto distances = dijkstra.runOptimized(0);
    std::vector<std::int64_t> correct_distances = {0, 1, 3, 6,
                                                   std::numeric_limits<std::int64_t>::max()};

    ASSERT_EQ(distances.distances()[1], correct_distances[1]);
    ASSERT_EQ(distances.distances()[2], correct_distances[2]);
}
