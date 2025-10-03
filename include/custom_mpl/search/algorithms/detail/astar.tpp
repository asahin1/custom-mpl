#ifndef CUSTOM_MPL_SEARCH_ALGORITHMS_DETAIL_ASTAR_TPP
#define CUSTOM_MPL_SEARCH_ALGORITHMS_DETAIL_ASTAR_TPP

#include <unordered_map>

#include "custom_mpl/search/core/result.hpp"
#include "custom_mpl/search/utils/reconstruct.hpp"

namespace custom_mpl::search::algorithms {
template <class N, class G, class IsGoalFunc, class H, class PQ,
          class ClosedSetPolicy, class ReopenPolicy, class Key>
custom_mpl::search::core::SearchResult<N>
astar(const G &graph, const N &start, const IsGoalFunc &is_goal, const H &h,
      PQ open, ClosedSetPolicy closed, ReopenPolicy reopen) {

  auto f = [&](const N &n, custom_mpl::search::core::Cost gval) {
    return static_cast<Key>(gval + h(n));
  };

  std::unordered_map<N, custom_mpl::search::core::Cost> g;
  std::unordered_map<N, N> came_from;

  g[start] = 0.0;
  open.push(start, f(start, 0.0));

  custom_mpl::search::core::SearchResult<N> res;

  while (!open.empty()) {
    N u = open.pop_min();
    if (closed.contains(u))
      continue;
    closed.insert(u);
    ++res.expanded;

    if (is_goal(u)) {
      res.found = true;
      res.cost = g[u];
      res.path =
          custom_mpl::search::utils::reconstruct_path<N>(came_from, start, u);
      return res;
    }

    for (auto &&e : graph.neighbors(u)) {
      const N &v = e.first;
      custom_mpl::search::core::Cost w =
          static_cast<custom_mpl::search::core::Cost>(e.second);
      if (w < 0) // should not have negative cost edge
        continue;
      custom_mpl::search::core::Cost cand = g[u] + w;
      auto it_gv = g.find(v);
      custom_mpl::search::core::Cost old_g =
          (it_gv == g.end()) ? custom_mpl::search::core::INF : it_gv->second;
      if (closed.contains(v) && !reopen.should_reopen(old_g, cand)) {
        continue;
      }

      if (cand < old_g) { // TODO: investigate different options here
        g[v] = cand;
        came_from[v] = u;
        open.push(v, f(v, cand));
        ++res.generated;
      }
    }
  }
  return res; // not found
}
} // namespace custom_mpl::search::algorithms

#endif