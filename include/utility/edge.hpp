#ifndef EDGE_HPP
#define EDGE_HPP

#include <cstdint>
#include <ostream>

namespace graph {

template <typename edgeType>
struct Edge {
    explicit Edge() = default;

    explicit Edge(std::int32_t from, std::int32_t to, edgeType edge)
        : m_from(from), m_to(to), m_edge(edge) {}

    Edge(const Edge &other) = default;
    Edge(Edge &&other) noexcept = default;
    Edge &operator=(const Edge &other) = default;
    Edge &operator=(Edge &&other) noexcept = default;

    [[nodiscard]] std::int32_t from() const {
        return m_from;
    }

    [[nodiscard]] std::int32_t to() const {
        return m_to;
    }

    [[nodiscard]] edgeType edge() const {
        return m_edge;
    }

private:
    std::int32_t m_from{};  // Номер вершины, из которой ведет ребро
    std::int32_t m_to{};    // Номер вершины, в которую ведет ребро
    edgeType m_edge;        // Ребро
};

}  // namespace graph

#endif  // EDGE_HPP
