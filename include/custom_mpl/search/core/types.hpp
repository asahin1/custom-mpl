#ifndef CUSTOM_MPL_SEARCH_CORE_TYPES_HPP
#define CUSTOM_MPL_SEARCH_CORE_TYPES_HPP

#include <cstddef>
#include <limits>

namespace custom_mpl::search::core {
using Cost = double;
inline constexpr Cost INF = std::numeric_limits<Cost>::infinity();

template <class Node> struct QItem {
  Node node;
  Cost f, g;
  size_t seq;
};

} // namespace custom_mpl::search::core

#endif