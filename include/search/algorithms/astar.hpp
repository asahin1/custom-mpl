#ifndef SEARCH_ALGORITHMS_ASTAR_HPP
#define SEARCH_ALGORITHMS_ASTAR_HPP

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#include "search/core/result.hpp"
#include "search/core/types.hpp"

namespace search::algorithms {
template <class N, class G, class H, class PQ, class Key = double>
core::SearchResult<N> astar(const G &graph, const N &start, const N &goal,
                            const H &h, PQ open);
}

#include "search/algorithms/detail/astar.tpp"

#endif