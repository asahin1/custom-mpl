#ifndef SEARCH_GRAPHS_ADJACENCYLISTGRAPH_HPP
#define SEARCH_GRAPHS_ADJACENCYLISTGRAPH_HPP

#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

namespace search::graphs {
template <class N = int, class W = double> class AdjacencyListGraph {
public:
  using Edge = std::pair<N, W>;
  std::vector<std::vector<Edge>> edges;

  explicit AdjacencyListGraph(std::size_t n = 0) : edges(n) {}

  void ensure_size(N id) {
    if (static_cast<std::size_t>(id) >= edges.size()) {
      edges.resize(static_cast<std::size_t>(id) + 1);
    }
  }

  void add_edge(N u, N v, W w) {
    ensure_size(std::max(u, v));
    edges[static_cast<std::size_t>(u)].emplace_back(v, w);
  }

  const std::vector<Edge> &neighbors(const N &u) const {
    return edges[static_cast<std::size_t>(u)];
  }
};
} // namespace search::graphs

#endif