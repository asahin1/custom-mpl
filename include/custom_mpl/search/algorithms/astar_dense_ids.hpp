#ifndef CUSTOM_MPL_SEARCH_ALGORITHMS_ASTARDENSEIDS_HPP
#define CUSTOM_MPL_SEARCH_ALGORITHMS_ASTARDENSEIDS_HPP

#include <algorithm>
#include <limits>
#include <unordered_map>
#include <vector>

#include "custom_mpl/search/core/result.hpp"

namespace custom_mpl::search::algorithms {
template <class Gid, class Hid, class PQ>
auto astar_dense_ids(const Gid &G, int s, int t, const Hid &h,
                     PQ open) -> search::core::SearchResult<int> {
  const int N = G.num_nodes();
  std::vector<double> g(N, std::numeric_limits<double>::infinity());
  std::vector<int> came_from(N, -1);
  std::vector<char> closed(N, 0);

  auto fkey = [&](int u) { return g[u] + h(u, t); };

  search::core::SearchResult<int> res;
  g[s] = 0.0;
  open.push(s, fkey(s));

  while (!open.empty()) {
    int u = open.pop_min();
    if (closed[u])
      continue;
    closed[u] = 1;
    ++res.expanded;
    if (u == t) {
      res.found = true;
      res.cost = g[u];
      break;
    }

    for (auto [v, w] : G.neighbors(u)) {
      if (w < 0)
        continue;
      double cand = g[u] + w;
      if (cand < g[v]) {
        g[v] = cand;
        came_from[v] = u;
        open.push(v, fkey(v));
        ++res.generated;
      }
    }
  }

  if (res.found) {
    std::vector<int> path;
    for (int cur = t; cur != -1; cur = came_from[cur])
      path.push_back(cur);
    std::reverse(path.begin(), path.end());
    res.path = std::move(path);
  }
  return res;
}
} // namespace search::algorithms

#endif