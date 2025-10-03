#ifndef CUSTOM_MPL_SEARCH_ALGORITHMS_DIJKSTRA_HPP
#define CUSTOM_MPL_SEARCH_ALGORITHMS_DIJKSTRA_HPP

#include "custom_mpl/search/algorithms/astar.hpp"
#include "custom_mpl/search/core/heuristic.hpp"

namespace search::algorithms {
template <class N, class G, class PQ, class Key = double>
inline core::SearchResult<N> dijkstra(const G &graph, const N &s, const N &t,
                                      PQ open) {
  return astar<N, G, search::core::ZeroHeuristic<N>, PQ, Key>(
      graph, s, t, search::core::ZeroHeuristic<N>{}, open);
}
} // namespace search::algorithms

#endif