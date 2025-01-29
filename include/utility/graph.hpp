#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>
#include <iostream>

struct Edge {
    explicit Edge() = default;

    explicit Edge(std::int32_t from, std::int32_t to, std::int32_t weight, const std::string& label = "");

    Edge(const Edge& other) = default;
    Edge(Edge&& other) noexcept = default;
    Edge& operator=(const Edge& other) = default;
    Edge& operator=(Edge&& other) noexcept = default;

    [[nodiscard]] std::int32_t from() const;
    [[nodiscard]] std::int32_t to() const;
    [[nodiscard]] std::int32_t weight() const;
    [[nodiscard]] std::string label() const;

private:
    std::int32_t m_from; // Номер вершины, из которой ведет ребро
    std::int32_t m_to; // Номер вершины, в которую ведет ребро
    std::int32_t m_weight; // Вес ребра
    std::string m_label; // Метка или строка, хранящаяся на ребре
};

struct AdjacencyListGraph {
    explicit AdjacencyListGraph(std::int32_t numVertices);

    void addEdge(std::int32_t from, std::int32_t to, std::int32_t weight, const std::string& label = "");

    void printEdges(std::ostream &ostream);

    std::int32_t numVertices() const;

    const std::vector<std::vector<Edge>>& getAdjList() const;

private:
    std::int32_t m_numVertices; // Количество вершин в графе
    std::vector<std::vector<Edge>> m_adjList; // Список смежности
};

#endif // GRAPH_HPP