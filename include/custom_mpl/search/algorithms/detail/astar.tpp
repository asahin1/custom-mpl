#ifndef CUSTOM_MPL_SEARCH_ALGORITHMS_DETAIL_ASTAR_TPP
#define CUSTOM_MPL_SEARCH_ALGORITHMS_DETAIL_ASTAR_TPP

#include <regex>
#include <unordered_map>

#include "custom_mpl/search/utils/reconstruct.hpp"

namespace search::algorithms {
template <class N, class G, class H, class PQ, class Key>
core::SearchResult<N> astar(const G &graph, const N &start, const N &goal,
                            const H &h, PQ open) {
  auto f = [&](const N &n, core::Cost gval) {
    return static_cast<Key>(gval + h(n, goal));
  };

  std::unordered_map<N, core::Cost> g;
  std::unordered_map<N, N> came_from;
  std::unordered_set<N> closed;

  g[start] = 0.0;
  open.push(start, f(start, 0.0));

  core::SearchResult<N> res;

  while (!open.empty()) {
    N u = open.pop_min();
    if (closed.find(u) != closed.end()) {
      // selected node is in closed set
      continue;
    }
    closed.insert(u);
    ++res.expanded;

    if (u == goal) {
      res.found = true;
      res.cost = g[u];
      res.path = search::utils::reconstruct_path(came_from, start, goal);
      return res;
    }

    for (auto &&e : graph.neighbors(u)) {
      const N &v = e.first;
      core::Cost w = static_cast<core::Cost>(e.second);
      if (w < 0) // should not have negative cost edge
        continue;
      core::Cost cand = g[u] + w;
      if (!g.count(v) ||
          cand < g[v]) { // TODO: investigate different options here
        g[v] = cand;
        came_from[v] = u;
        open.push(v, f(v, cand));
        ++res.generated;
      }
    }
  }
  return res; // not found
}
} // namespace search::algorithms

#endif