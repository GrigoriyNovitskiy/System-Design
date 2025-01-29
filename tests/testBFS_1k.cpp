#include "gtest/gtest.h"
#include "bfs1_k.hpp"

TEST(BFS_1kTest, BaseTest1_4) {
    AdjacencyListGraph graph(4);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 1);

    BFS_1k bfs(graph, 0, 3);
    std::vector <std::int32_t> distances = bfs.run();
    std::vector <std::int32_t> correct_distances = {0, 3, 1, 2};
    ASSERT_EQ(distances, correct_distances);
}

TEST(BFS_1kTest, BaseTest1_1) {
    AdjacencyListGraph graph(4);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);

    BFS_1k bfs(graph, 0, 1);
    std::vector <std::int32_t> distances = bfs.run();
    std::vector <std::int32_t> correct_distances = {0, 1, 1, 2};
    ASSERT_EQ(distances, correct_distances);
}

TEST(BFS_1kTest, BaseTest1_5) {
    AdjacencyListGraph graph(5);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 3);
    graph.addEdge(3, 4, 1);

    BFS_1k bfs(graph, 0, 3);
    std::vector <std::int32_t> distances = bfs.run();
    std::vector <std::int32_t> correct_distances = {0, 1, 3, 6, 7, std::numeric_limits<std::int32_t>::max()};
    ASSERT_EQ(distances, correct_distances);
}
