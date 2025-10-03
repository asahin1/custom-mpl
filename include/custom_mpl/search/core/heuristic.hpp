#ifndef CUSTOM_MPL_SEARCH_CORE_HEURISTIC_HPP
#define CUSTOM_MPL_SEARCH_CORE_HEURISTIC_HPP

namespace search::core {
template <class N> struct ZeroHeuristic {
  double operator()(const N &, const N &) const noexcept { return 0.0; }
};
} // namespace search::core

#endif