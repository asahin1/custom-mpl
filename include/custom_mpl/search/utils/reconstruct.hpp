#ifndef CUSTOM_MPL_SEARCH_UTILS_RECONSTRUCT_HPP
#define CUSTOM_MPL_SEARCH_UTILS_RECONSTRUCT_HPP

#include <algorithm>
#include <vector>

namespace custom_mpl::search::utils {
template <class Store, class Node>
inline std::vector<Node> reconstruct_path(const Store &nodes, size_t goal_id,
                                          size_t no_parent_sentinel) {
  std::vector<Node> path;
  for (size_t id = goal_id; id != no_parent_sentinel; id = nodes[id].parent) {
    path.push_back(nodes[id].node);
  }
  std::reverse(path.begin(), path.end());
  return path;
}
} // namespace custom_mpl::search::utils

#endif