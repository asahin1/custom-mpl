#ifndef CUSTOM_MPL_SEARCH_CORE_RESULT_HPP
#define CUSTOM_MPL_SEARCH_CORE_RESULT_HPP

#include <cstddef>
#include <vector>

#include "types.hpp"

namespace custom_mpl::search::core {
template <class N> struct SearchResult {
  std::vector<N> path;
  Cost cost = INF;
  bool found = false;
  std::size_t expanded = 0;
  std::size_t generated = 0;
};
} // namespace search::core

#endif