#ifndef CUSTOM_MPL_SEARCH_ALGORITHMS_DIJKSTRA_HPP
#define CUSTOM_MPL_SEARCH_ALGORITHMS_DIJKSTRA_HPP

#include "custom_mpl/search/algorithms/astar.hpp"
#include "custom_mpl/search/core/heuristic.hpp"

namespace custom_mpl::search::algorithms {
template <class N, class G, class IsGoalFunc, class PQ, class Key = double>
inline core::SearchResult<N> dijkstra(const G &graph, const N &s,
                                      const IsGoalFunc &is_goal, PQ open) {
  return astar_classic<N, G, IsGoalFunc, search::core::ZeroHeuristic<N>, PQ,
                       Key>(graph, s, is_goal, search::core::ZeroHeuristic<N>{},
                            open);
}
} // namespace custom_mpl::search::algorithms

#endif