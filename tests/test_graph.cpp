#include "graph.hpp"
#include "gtest/gtest.h"

TEST(GraphTest, AdjacencyGraph) {
    graph::AdjacencyListGraph<int> graph(4, false);

    ASSERT_EQ(4, graph.numberVertices());
    ASSERT_EQ(0, graph.numberEdges());
    ASSERT_FALSE(graph.isDirected());

    ASSERT_NO_THROW(graph.addEdge(0, 1, 1));
    ASSERT_TRUE(graph.isVertexesConnected(0, 1));

    ASSERT_THROW(graph.addEdge(-1, 0, 1), std::domain_error);
    ASSERT_THROW(static_cast<void>(graph.isVertexesConnected(-1, 0)), std::domain_error);

    ASSERT_EQ(1, graph.numberEdges());

    std::stringstream ss;
    graph.printEdges(ss);
    ASSERT_EQ(ss.str(), "0 -> 1 edge: 1\n1 -> 0 edge: 1\n");

    ASSERT_NO_THROW(graph.addEdge(2, 1, 1));

    std::vector<graph::Edge<int>> neighbours;
    std::vector<graph::Edge<int>> correctNeighbours = {graph::Edge(1, 0, 1), graph::Edge(1, 2, 1)};
    graph.getNeighbours(1, neighbours);
    ASSERT_EQ(neighbours, correctNeighbours);
}

TEST(GraphTest, MatrixGraph) {
    graph::AdjacencyMatrixGraph<int> graph(4, false);

    ASSERT_EQ(4, graph.numberVertices());
    ASSERT_EQ(0, graph.numberEdges());
    ASSERT_FALSE(graph.isDirected());

    ASSERT_NO_THROW(graph.addEdge(0, 1, 1));
    ASSERT_TRUE(graph.isVertexesConnected(0, 1));

    ASSERT_THROW(graph.addEdge(-1, 0, 1), std::domain_error);
    ASSERT_THROW(static_cast<void>(graph.isVertexesConnected(-1, 0)), std::domain_error);

    ASSERT_EQ(1, graph.numberEdges());

    std::stringstream ss;
    graph.printEdges(ss);
    ASSERT_EQ(ss.str(), "0 -> 1 edge: 1\n1 -> 0 edge: 1\n");

    ASSERT_NO_THROW(graph.addEdge(2, 1, 1));

    std::vector<graph::Edge<int>> neighbours;
    std::vector<graph::Edge<int>> correctNeighbours = {graph::Edge(1, 0, 1), graph::Edge(1, 2, 1)};
    graph.getNeighbours(1, neighbours);
    ASSERT_EQ(neighbours, correctNeighbours);
}
