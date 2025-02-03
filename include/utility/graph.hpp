#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <optional>
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

    virtual void printEdges(std::ostream& ostream) const = 0;

    virtual void getNeighbours(std::int32_t vertex,
                               std::vector<Edge<edgeType>>& neighbours) const = 0;

    [[nodiscard]] virtual bool isVertexesConnected(std::int32_t from, std::int32_t to) const = 0;

    [[nodiscard]] bool isVertexValid(std::int32_t vertex) const {
        return 0 <= vertex && vertex < m_numberVertices;
    }

    [[nodiscard]] std::int32_t numberVertices() const { return m_numberVertices; }

    [[nodiscard]] std::int32_t numberEdges() const { return m_numberEdges; }

    [[nodiscard]] bool isDirected() const { return m_isDirected; }

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
        if (!this->isVertexValid(from) || !this->isVertexValid(to)) {
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

    void printEdges(std::ostream& ostream) const override {
        for (std::int32_t vertex = 0; vertex < this->m_numberVertices; vertex++) {
            for (const auto& edge : m_adjList[vertex]) {
                ostream << edge.from() << " -> " << edge.to() << " edge: " << edge.edge() << "\n";
            }
        }
    }

    void getNeighbours(std::int32_t vertex,
                       std::vector<Edge<edgeType>>& neighbours) const override {
        if (!this->isVertexValid(vertex)) {
            std::stringstream error;
            error << "Vertex is out of bounds: " << vertex << '\n';
            throw std::domain_error(error.str());
        }
        neighbours = m_adjList[vertex];
    }

    [[nodiscard]] bool isVertexesConnected(std::int32_t from, std::int32_t to) const override {
        if (!this->isVertexValid(from) || !this->isVertexValid(to)) {
            std::stringstream error;
            error << "Vertex is out of bounds: " << from << " -> " << to << '\n';
            throw std::domain_error(error.str());
        }
        return std::any_of(m_adjList[from].begin(), m_adjList[from].end(),
                           [to](Edge<edgeType> neighbour) { return neighbour.to() == to; });
    }

private:
    std::vector<std::vector<Edge<edgeType>>> m_adjList;  // Список смежности
};

template <typename edgeType>
class AdjacencyMatrixGraph : public Graph<edgeType> {
public:
    explicit AdjacencyMatrixGraph(std::int32_t numberVertices, bool isDirected)
        : Graph<edgeType>(numberVertices, isDirected),
          m_adjMatrix(numberVertices, std::vector<std::optional<Edge<edgeType>>>(numberVertices)) {}

    void addEdge(std::int32_t from, std::int32_t to, edgeType edge) override {
        if (!this->isVertexValid(from) || !this->isVertexValid(to)) {
            std::stringstream error;
            error << "Vertex is out of bounds: " << from << " -> " << to << " edge = " << edge
                  << '\n';
            throw std::domain_error(error.str());
        }

        m_adjMatrix[from][to].emplace(from, to, edge);
        if (!this->m_isDirected) {
            m_adjMatrix[to][from].emplace(to, from, edge);
        }
        this->m_numberEdges++;
    }

    void printEdges(std::ostream& ostream) const override {
        for (std::int32_t u = 0; u < this->m_numberVertices; u++) {
            for (std::int32_t v = 0; v < this->m_numberVertices; v++) {
                if (m_adjMatrix[u][v].has_value()) {
                    ostream << u << " -> " << v << " edge: " << m_adjMatrix[u][v].value().edge()
                            << "\n";
                }
            }
        }
    }

    void getNeighbours(std::int32_t vertex,
                       std::vector<Edge<edgeType>>& neighbours) const override {
        if (!this->isVertexValid(vertex)) {
            std::stringstream error;
            error << "Vertex is out of bounds: " << vertex << '\n';
            throw std::domain_error(error.str());
        }

        for (const auto& neighbour : m_adjMatrix[vertex]) {
            if (neighbour.has_value()) {
                neighbours.emplace_back(neighbour.value());
            }
        }
    }

    [[nodiscard]] bool isVertexesConnected(std::int32_t from, std::int32_t to) const override {
        if (!this->isVertexValid(from) || !this->isVertexValid(to)) {
            std::stringstream error;
            error << "Vertex is out of bounds: " << from << " -> " << to << '\n';
            throw std::domain_error(error.str());
        }
        return m_adjMatrix[from][to].has_value();
    }

private:
    std::vector<std::vector<std::optional<Edge<edgeType>>>> m_adjMatrix;  // Матрица смежности
};

};  // namespace graph

#endif  // GRAPH_HPP