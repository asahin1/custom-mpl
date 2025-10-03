#ifndef CUSTOM_MPL_SEARCH_UTILS_RECONSTRUCT_HPP
#define CUSTOM_MPL_SEARCH_UTILS_RECONSTRUCT_HPP

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace custom_mpl::search::utils {
template <class N>
inline std::vector<N>
reconstruct_path(const std::unordered_map<N, N> &came_from, N start, N goal) {
  // TODO: understand the choice of the unordered_map to store the came_from
  // information
  std::vector<N> path;
  N cur = goal;
  path.push_back(cur);
  while (cur != start) {
    auto it = came_from.find(cur);
    if (it == came_from.end()) {
      return {};
    }
    cur = it->second;
    path.push_back(cur);
  }
  std::reverse(path.begin(), path.end());
  return path;
}
} // namespace custom_mpl::search::utils

#endif