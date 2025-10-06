#ifndef CUSTOM_MPL_SEARCH_ALGORITHMS_ASTAR_HPP
#define CUSTOM_MPL_SEARCH_ALGORITHMS_ASTAR_HPP

#include "custom_mpl/search/core/result.hpp"
#include "custom_mpl/search/datastructures/pq_binary_heap.hpp"
#include "custom_mpl/search/policies/closed_set.hpp"
#include "custom_mpl/search/policies/reopen.hpp"

namespace custom_mpl::search::algorithms {
// N: Node, G: Graph, H: Heuristic, PQ: Priority Queue, Key: Cost
template <class N, class G, class IsGoalFunc, class H, class PQ,
          class ClosedSetPolicy, class ReopenPolicy, class Key = double>
custom_mpl::search::core::SearchResult<N>
astar(const G &graph, const N &start, const IsGoalFunc &is_goal, const H &h,
      PQ open, ClosedSetPolicy closed, ReopenPolicy reopen);
} // namespace custom_mpl::search::algorithms

#include "custom_mpl/search/algorithms/detail/astar.tpp"

namespace custom_mpl::search::algorithms {
template <class N, class G, class IsGoalFunc, class H, class PQ,
          class Key = double>
auto astar_classic(
    const G &g, const N &s, const IsGoalFunc &is_goal, const H &h,
    PQ open) { // astar implementation based on Hart et al. (1968)
  return astar<N, G, IsGoalFunc, H, PQ>(
      g, s, is_goal, h, open,
      custom_mpl::search::policies::ClosedSetHash<N>{}, // with closed list
      custom_mpl::search::policies::ReopenIfBetter{}    // and reopening
  );
}
} // namespace custom_mpl::search::algorithms
// namespace custom_mpl::search::algorithms

#endif