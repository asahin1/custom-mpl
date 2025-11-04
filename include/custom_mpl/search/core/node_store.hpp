#ifndef CUSTOMMPL_SEARCH_CORE_NODESTORE_HPP
#define CUSTOMMPL_SEARCH_CORE_NODESTORE_HPP

#include "custom_mpl/search/utils/hash_utils.hpp"

namespace custom_mpl::search::core {
template <class Node> struct NodeStore {
  using NodeHash = utils::DerefHash<Node>;
  using NodeEq = utils::DerefEq<Node>;

  static constexpr size_t kNoParent = std::numeric_limits<size_t>::max();

  struct NodeInfo {
    const Node node;
    core::Cost g;
    size_t parent;
    bool closed;
  };

  std::deque<NodeInfo> nodes;

  std::unordered_map<const Node *, size_t, NodeHash, NodeEq> node_to_id;

  size_t get_or_create(const Node &n) {
    Node probe = n;
    const Node *p = &probe;
    auto it = node_to_id.find(p);
    if (it != node_to_id.end()) {
      return it->second;
    }
    NodeInfo &stored =
        nodes.emplace_back(NodeInfo{n, core::INF, kNoParent, false});
    const Node *id = &stored.node;
    size_t index = nodes.size() - 1;
    node_to_id.emplace(id, index);
    return index;
  }
};
} // namespace custom_mpl::search::core

#endif