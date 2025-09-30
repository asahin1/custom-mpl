#ifndef SEARCH_CORE_SOLVE_HPP
#define SEARCH_CORE_SOLVE_HPP

#include "heuristic_lift.hpp"
#include "search/algorithms/astar_dense_ids.hpp"
#include "search/core/heuristic_lift.hpp"
#include "search/datastructures/pq_binary_heap.hpp"
#include "search/graphs/auto_intern.hpp"

namespace search::core {
template <class N, class G, class H,
          class PQ = search::datastructures::BinaryHeapPQ<int, double>>
auto solve_astar_easy(const G &g, const std::vector<N> &all_nodes,
                      const N &start, const N &goal, const H &h, PQ pq = PQ{}) {
  search::graphs::AutoInterned<G, N> intern(g, all_nodes);
  int s = intern.index.id(start);
  int t = intern.index.id(goal);
  core::LiftHeuristicToIds<N, H, decltype(intern.index)> hid{&h, &intern.index};

  auto res_ids =
      search::algorithms::astar_dense_ids(intern.Gid, s, t, hid, std::move(pq));

  search::core::SearchResult<N> out;
  out.found = res_ids.found;
  out.cost = res_ids.cost;
  out.expanded = res_ids.expanded;
  out.generated = res_ids.generated;
  for (int uid : res_ids.path)
    out.path.push_back(intern.index.from_id(uid));
  return out;
}
} // namespace search::core

#endif