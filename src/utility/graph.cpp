#include "graph.hpp"

Edge::Edge(std::int32_t from, std::int32_t to, std::int32_t weight, const std::string &label)
    : m_from(from), m_to(to), m_weight(weight), m_label(label) {}

std::int32_t Edge::to() const { return m_to; }

std::int32_t Edge::weight() const { return m_weight; }

std::string Edge::label() const { return m_label; }

std::int32_t Edge::from() const { return m_from; }

void AdjacencyListGraph::printEdges(std::ostream &ostream) {
    for (std::int32_t vertex = 0; vertex < m_numVertices; ++vertex) {
        for (const auto &edge : m_adjList[vertex]) {
            ostream << vertex << " -> " << edge.to() << " weight: " << edge.weight()
                    << " label: " << edge.label() << "\n";
        }
    }
}

AdjacencyListGraph::AdjacencyListGraph(std::int32_t numVertices)
    : m_numVertices(numVertices), m_adjList(numVertices) {}

void AdjacencyListGraph::addEdge(std::int32_t from, std::int32_t to, std::int32_t weight, const std::string &label) {
    if (from < 0 || from > m_numVertices || to < 0 || to > m_numVertices) {
        throw std::domain_error("vertex is out of bounds: " + std::to_string(from) + " -> " +
                                std::to_string(to) + " weight = " + std::to_string(weight) +
                                " label = " + label);
    }

    m_adjList[from].emplace_back(from, to, weight, label);
}

std::int32_t AdjacencyListGraph::numVertices() const {
    return m_numVertices;
}

const std::vector<std::vector<Edge>> &AdjacencyListGraph::getAdjList() const {
    return m_adjList;
}
