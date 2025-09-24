#ifndef SEARCH_CORE_TYPES_HPP
#define SEARCH_CORE_TYPES_HPP

#include <limits>

namespace search::core {
using Cost = double;
inline constexpr Cost INF = std::numeric_limits<Cost>::infinity();
} // namespace search::core

#endif