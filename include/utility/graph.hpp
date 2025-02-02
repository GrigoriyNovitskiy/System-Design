#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "edge.hpp"

namespace graph {

template <typename edgeType>
class Graph {
public:
    explicit Graph(std::int32_t numberVertices, bool isDirected)
        : m_numberVertices(numberVertices), m_numberEdges(0), m_isDirected(isDirected) {}

    virtual ~Graph() = default;

    virtual void addEdge(std::int32_t from, std::int32_t to, edgeType edge) = 0;

    virtual void printEdges(std::ostream &ostream) const = 0;

    [[nodiscard]] std::int32_t numberVertices() const {
        return m_numberVertices;
    }

    [[nodiscard]] std::int32_t numberEdges() const {
        return m_numberEdges;
    }

protected:
    std::int32_t m_numberVertices;
    std::int32_t m_numberEdges;
    bool m_isDirected;
};

template <typename edgeType>
struct AdjacencyListGraph : public Graph<edgeType> {
    explicit AdjacencyListGraph(std::int32_t numberVertices, bool isDirected)
        : Graph<edgeType>(numberVertices, isDirected), m_adjList(numberVertices) {}

    void addEdge(std::int32_t from, std::int32_t to, edgeType edge) override {
        if (from < 0 || from > this->m_numberVertices || to < 0 || to > this->m_numberVertices) {
            std::stringstream error;
            error << "Vertex is out of bounds: " << from << " -> " << to << " edge = " << edge
                  << '\n';
            throw std::domain_error(error.str());
        }

        m_adjList[from].emplace_back(from, to, edge);
        if (!this->m_isDirected) {
            m_adjList[to].emplace_back(to, from, edge);
        }
        this->m_numberEdges++;
    }

    void printEdges(std::ostream &ostream) const {
        for (std::int32_t vertex = 0; vertex < this->m_numberVertices; vertex++) {
            for (const auto &edge : m_adjList[vertex]) {
                ostream << edge.from() << " -> " << edge.to() << " edge: " << edge.edge() << "\n";
            }
        }
    }

    const std::vector<Edge<edgeType>> &getNeighbours(std::int32_t vertex) const {
        if (vertex < 0 || vertex > this->m_numberVertices) {
            std::stringstream error;
            error << "Vertex is out of bounds: " << vertex << '\n';
            throw std::domain_error(error.str());
        }
        return m_adjList[vertex];
    }

private:
    std::vector<std::vector<Edge<edgeType>>> m_adjList;  // Список смежности
};

template <typename edgeType>
class AdjacencyMatrixGraph : public Graph<edgeType> {
public:
    explicit AdjacencyMatrixGraph(std::int32_t numberVertices, bool isDirected)
        : Graph<edgeType>(numberVertices, isDirected),
          m_adjMatrix(numberVertices, std::vector<edgeType>(numberVertices)) {}

    void addEdge(std::int32_t from, std::int32_t to, edgeType edge) override {
        if (from < 0 || from > this->m_numberVertices || to < 0 || to > this->m_numberVertices) {
            std::stringstream error;
            error << "Vertex is out of bounds: " << from << " -> " << to << " edge = " << edge
                  << '\n';
            throw std::domain_error(error.str());
        }

        m_adjMatrix[from][to] = edge;
        if (!this->m_isDirected) {
            m_adjMatrix[to][from] = edge;
        }
        this->m_numberEdges++;
    }

    void printEdges(std::ostream &ostream) const override {
        for (std::int32_t u = 0; u < this->m_numberVertices; u++) {
            for (std::int32_t v = 0; v < this->m_numberVertices; v++) {
                if (static_cast<bool>(m_adjMatrix[u][v])) {
                    ostream << u << " -> " << v << " edge: " << m_adjMatrix[u][v] << "\n";
                }
            }
        }
    }

    const std::vector<Edge<edgeType>> &getNeighbours(std::int32_t vertex) const {
        if (vertex < 0 || vertex > this->m_numberVertices) {
            std::stringstream error;
            error << "Vertex is out of bounds: " << vertex << '\n';
            throw std::domain_error(error.str());
        }
        return m_adjMatrix[vertex];
    }

private:
    std::vector<std::vector<Edge<edgeType>>>m_adjMatrix;  // Матрица смежности
};

};  // namespace graph

#endif  // GRAPH_HPP