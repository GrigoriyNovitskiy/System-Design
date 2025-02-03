#include "bfs_1k.hpp"
#include "gtest/gtest.h"

TEST(BFS_1kTest, BaseTestList1) {
    graph::AdjacencyListGraph<int> graph(4, false);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 1);

    graph::BFS_1k bfs(graph, 3);
    auto bfsResult = bfs.run(0);
    std::vector<std::int32_t> correct_distances = {0, 3, 1, 2};
    ASSERT_EQ(bfsResult.distances(), correct_distances);
    std::vector<std::int32_t> correct_accessibility = {1, 1, 1, 1};
    ASSERT_EQ(bfsResult.accessibility(), correct_accessibility);
}

TEST(BFS_1kTest, BaseTestList2) {
    graph::AdjacencyListGraph<int> graph(4, false);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);

    graph::BFS_1k bfs(graph, 1);
    auto bfsResult = bfs.run(0);
    std::vector<std::int32_t> correct_distances = {0, 1, 1, 2};
    ASSERT_EQ(bfsResult.distances(), correct_distances);
    std::vector<std::int32_t> correct_accessibility = {1, 1, 1, 1};
    ASSERT_EQ(bfsResult.accessibility(), correct_accessibility);
}

TEST(BFS_1kTest, BaseTestList3) {
    graph::AdjacencyListGraph<int> graph(5, false);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 3);

    graph::BFS_1k bfs(graph, 3);
    auto bfsResult = bfs.run(0);
    std::vector<std::int32_t> correct_distances = {0, 1, 3, 6,
                                                   std::numeric_limits<std::int32_t>::max()};
    ASSERT_EQ(bfsResult.distances(), correct_distances);
    std::vector<std::int32_t> correct_accessibility = {1, 1, 1, 1, 0};
    ASSERT_EQ(bfsResult.accessibility(), correct_accessibility);
}

TEST(BFS_1kTest, BaseTestMatrix1) {
    graph::AdjacencyMatrixGraph<int> graph(5, false);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 3);

    graph::BFS_1k bfs(graph, 3);
    auto bfsResult = bfs.run(0);
    std::vector<std::int32_t> correct_distances = {0, 1, 3, 6,
                                                   std::numeric_limits<std::int32_t>::max()};
    ASSERT_EQ(bfsResult.distances(), correct_distances);
    std::vector<std::int32_t> correct_accessibility = {1, 1, 1, 1, 0};
    ASSERT_EQ(bfsResult.accessibility(), correct_accessibility);
}

struct Edge {
    explicit Edge(std::int32_t weight, const std::string& label)
        : m_weight(weight), m_label(label) {}

    Edge operator+(const Edge& edge) const {
        return Edge(m_weight + edge.m_weight, m_label + edge.m_label);
    }

    [[nodiscard]] std::int32_t weight() const { return m_weight; }

    [[nodiscard]] std::int32_t label() const { return m_weight; }

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

TEST(BFS_1kTest, BaseTestCustomEdge1) {
    graph::AdjacencyMatrixGraph<Edge> graph(5, false);
    graph.addEdge(0, 1, Edge(1, "aaa"));
    graph.addEdge(1, 2, Edge(2, "bbb"));
    graph.addEdge(2, 3, Edge(3, "ccc"));

    graph::BFS_1k bfs(graph, 3);
    auto bfsResult = bfs.run(0);
    std::vector<std::int32_t> correct_distances = {0, 1, 3, 6,
                                                   std::numeric_limits<std::int32_t>::max()};
    ASSERT_EQ(bfsResult.distances(), correct_distances);
    std::vector<std::int32_t> correct_accessibility = {1, 1, 1, 1, 0};
    ASSERT_EQ(bfsResult.accessibility(), correct_accessibility);
}
