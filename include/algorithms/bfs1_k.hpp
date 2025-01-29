#include "graph.hpp"

class BFS_1k {
public:
    BFS_1k(AdjacencyListGraph& graph, int startVertex, int maxWeight);

    // Метод для запуска алгоритма 1-k BFS
    std::vector<int> run();

private:
    AdjacencyListGraph& m_graph;
    std::int32_t m_startVertex;
    std::int32_t m_maxWeight;
};
