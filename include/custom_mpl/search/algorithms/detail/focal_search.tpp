#ifndef CUSTOMMPL_SEARCH_ALGORITHMS_DETAIL_FOCALSEARCH_TPP
#define CUSTOMMPL_SEARCH_ALGORITHMS_DETAIL_FOCALSEARCH_TPP

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

template <class Node, class Graph, class IsGoalFunc, class HeuristicOpen,
          class HeuristicFocal>
custom_mpl::search::core::SearchResult<Node>
focal_search(const Graph &graph, const Node &start, const IsGoalFunc &is_goal,
             const HeuristicOpen &h, const HeuristicFocal &h_f, double eps) {

  using NodeStore_t = core::NodeStore<Node>;
  using NodeInfo = typename NodeStore_t::NodeInfo;
  using NodeContainer_t = std::deque<NodeInfo>;

  auto f = [&](const NodeInfo &n_info) { return h(n_info.node) + n_info.g; };

  NodeStore_t node_store;
  auto start_index = node_store.get_or_create(start);
  core::Cost g_start = 0.0;
  node_store.nodes[start_index].g = g_start;

  custom_mpl::search::datastructures::OpenList<
      custom_mpl::search::policies::AStarDeeperFirst,
      custom_mpl::search::datastructures::IntrusiveHeapMaker>
      open;

  custom_mpl::search::datastructures::OpenList<
      custom_mpl::search::policies::FocalHeuristicDeeperFirst>
      focal;

  custom_mpl::search::policies::ClosedFlag closed;
  custom_mpl::search::policies::ReopenIfBetter reopen;

  size_t seq{0};
  open.push(start_index, g_start, h(start), seq);
  focal.push(start_index, g_start, h_f(start), seq);
  seq++;

  custom_mpl::search::core::SearchResult<Node> res;
  bool bound_update_required = false;
  while (!open.empty()) {
    bound_update_required = false;

    auto head_it = open.top();
    NodeInfo &head_info = node_store.nodes[head_it.id];
    auto f_min = f(head_info);

    // We pop from focal
    auto it = focal.pop_min();
    NodeInfo &u_info = node_store.nodes[it.id];

    // Need to remove the same node from open too (requires delete operation)
    // Maybe not if we force a closed set to be used
    if (it.id == head_it.id) {
      open.pop_min(); // Does it make sense to pop it if it's at top?
      bound_update_required = true;
    }

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
        auto h_val = h(v_info.node);
        open.push(v_idx, cand, h_val, seq++);
        if (h_val + cand <= eps * f_min) {
          focal.push(v_idx, cand, h_f(v_info.node), seq++);
        }
        closed.reopen(v_info.closed);
        ++res.generated;
      }
    }

    if (!open.empty() && bound_update_required) {
      auto new_head_it = open.top();
      NodeInfo &new_head_info = node_store.nodes[new_head_it.id];
      auto new_f_min = f(new_head_info);
      for (auto op_it = open.begin(); op_it != open.end();
           ++op_it) { // Are we able to iterate over open?
        NodeInfo &op_info = node_store.nodes[op_it->id];
        if (f(op_info) > f_min || f(op_info) <= new_f_min) {
          focal.push(op_it->id, op_info.g, h_f(op_info.node), seq++);
        }
      }
    }
  }
  return res;
}
} // namespace custom_mpl::search::algorithms

#endif