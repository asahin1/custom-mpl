#ifndef CUSTOM_MPL_SEARCH_CORE_TYPES_HPP
#define CUSTOM_MPL_SEARCH_CORE_TYPES_HPP

#include <limits>

namespace custom_mpl::search::core {
using Cost = double;
inline constexpr Cost INF = std::numeric_limits<Cost>::infinity();
} // namespace search::core

#endif