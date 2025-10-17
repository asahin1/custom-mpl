#ifndef CUSTOM_MPL_SEARCH_ALGORITHMS_DIJKSTRA_HPP
#define CUSTOM_MPL_SEARCH_ALGORITHMS_DIJKSTRA_HPP

#include "custom_mpl/search/algorithms/astar.hpp"
#include "custom_mpl/search/core/heuristic.hpp"

namespace custom_mpl::search::algorithms {
template <class Node, class Graph, class IsGoalFunc>
inline core::SearchResult<Node> dijkstra(const Graph &graph, const Node &start,
                                         const IsGoalFunc &is_goal) {
  return astar_classic(graph, start, is_goal,
                       search::core::ZeroHeuristic<Node>{});
}
} // namespace custom_mpl::search::algorithms

#endif