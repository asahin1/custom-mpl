#ifndef CUSTOM_MPL_SEARCH_ALGORITHMS_ASTAR_HPP
#define CUSTOM_MPL_SEARCH_ALGORITHMS_ASTAR_HPP

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#include "custom_mpl/search/core/result.hpp"
#include "custom_mpl/search/core/types.hpp"

namespace custom_mpl::search::algorithms {
template <class N, class G, class H, class PQ, class Key = double>
core::SearchResult<N> astar(const G &graph, const N &start, const N &goal,
                            const H &h, PQ open);
}

#include "custom_mpl/search/algorithms/detail/astar.tpp"

#endif