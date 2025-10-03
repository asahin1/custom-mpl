#ifndef CUSTOM_MPL_SEARCH_GRAPHS_INTADJ_HPP
#define CUSTOM_MPL_SEARCH_GRAPHS_INTADJ_HPP

#include <utility>
#include <vector>

namespace search::graphs {
struct IntAdj {
  std::vector<std::vector<std::pair<int, double>>> adj;
  explicit IntAdj(int n = 0) : adj(n) {}
  void add_edge(int u, int v, double w) { adj[u].push_back({v, w}); }
  const auto &neighbors(int u) const { return adj[u]; }
  int num_nodes() const { return (int)adj.size(); }
};
} // namespace search::graphs

#endif