#ifndef CUSTOM_MPL_SEARCH_ALGORITHMS_ASTARDENSEIDS_HPP
#define CUSTOM_MPL_SEARCH_ALGORITHMS_ASTARDENSEIDS_HPP

#include "custom_mpl/search/core/result.hpp"

namespace custom_mpl::search::algorithms {
template <class Gid, class Hid, class PQ>
custom_mpl::search::core::SearchResult<int>
astar_dense_ids(const Gid &G, int s, int t, const Hid &h, PQ open);
}

#include "custom_mpl/search/algorithms/detail/astar_dense_ids.tpp"

#endif