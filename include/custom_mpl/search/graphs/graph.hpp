#ifndef CUSTOM_MPL_SEARCH_GRAPHS_GRAPH_HPP
#define CUSTOM_MPL_SEARCH_GRAPHS_GRAPH_HPP

#include <utility>
#include <vector>

/*
Requirements for a GraphT used with search algorithms:
- const auto& neighbors(const NodeT& u) const;
  returns an iterable (e.g., std::vector<std::pair<NodeT,double>>) of outgoing
edges.
- Edge weights must be >= 0 (A* - Dijkstra assumption).
- NodeT must be usable as an unordered_map key if you use default impls
(hashable or custom hash). Optional:
- size(), bounds(), in_bounds(node) for grids
- capability flags if needed in the future
*/

namespace search::core {} // namespace search::core

#endif