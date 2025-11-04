#ifndef CUSTOM_MPL_SEARCH_ALGORITHMS_DETAIL_ASTAR_TPP
#define CUSTOM_MPL_SEARCH_ALGORITHMS_DETAIL_ASTAR_TPP

#include <cstddef>
#include <deque>
#include <limits>
#include <unordered_map>

#include "custom_mpl/search/core/node_store.hpp"
#include "custom_mpl/search/core/result.hpp"
#include "custom_mpl/search/core/types.hpp"
#include "custom_mpl/search/datastructures/open_list.hpp"
#include "custom_mpl/search/utils/hash_utils.hpp"
#include "custom_mpl/search/utils/reconstruct.hpp"

namespace custom_mpl::search::algorithms {

template <class Node, class Graph, class IsGoalFunc, class Heuristic,
          class OrderingPolicy, class ClosedSetPolicy, class ReopenPolicy>
custom_mpl::search::core::SearchResult<Node> generalized_astar(
    const Graph &graph, const Node &start, const IsGoalFunc &is_goal,
    const Heuristic &h,
    custom_mpl::search::datastructures::OpenList<OrderingPolicy> &open,
    ClosedSetPolicy closed, ReopenPolicy reopen) {

  using NodeStore_t = core::NodeStore<Node>;
  using NodeInfo = typename NodeStore_t::NodeInfo;
  using NodeContainer_t = std::deque<NodeInfo>;

  NodeStore_t node_store;

  auto start_index = node_store.get_or_create(start);
  core::Cost g_start = 0.0;
  node_store.nodes[start_index].g = g_start;

  size_t seq{0};
  open.push(start_index, g_start, h(start), seq++);

  custom_mpl::search::core::SearchResult<Node> res;

  while (!open.empty()) {
    auto it = open.pop_min();
    NodeInfo &u_info = node_store.nodes[it.id];
    if (it.g_at_push != u_info.g) // popped node is stale
      continue;
    if (closed.is_closed(u_info.closed)) // popped node is in closed
      continue;
    closed.mark_closed(u_info.closed);
    ++res.expanded;

    if (is_goal(u_info.node)) {
      res.found = true;
      res.cost = u_info.g;
      res.path =
          custom_mpl::search::utils::reconstruct_path<NodeContainer_t, Node>(
              node_store.nodes, it.id, NodeStore_t::kNoParent);
      return res;
    }

    for (auto &&e : graph.neighbors(u_info.node)) {
      const Node &v = e.first;
      custom_mpl::search::core::Cost w =
          static_cast<custom_mpl::search::core::Cost>(e.second);
      if (w < 0) // should not have negative cost edge
        continue;
      custom_mpl::search::core::Cost cand = u_info.g + w;
      auto v_idx = node_store.get_or_create(v);
      NodeInfo &v_info = node_store.nodes[v_idx];
      custom_mpl::search::core::Cost old_g = v_info.g;
      if (closed.is_closed(v_info.closed) &&
          !reopen.should_reopen(old_g, cand)) {
        continue;
      }

      if (cand < old_g) {
        v_info.g = cand;
        v_info.parent = it.id;
        open.push(v_idx, cand, h(v_info.node), seq);
        closed.reopen(v_info.closed);
        ++res.generated;
      }
    }
  }
  return res; // not found
}
} // namespace custom_mpl::search::algorithms

#endif