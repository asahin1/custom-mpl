#ifndef CUSTOMMPL_SEARCH_ALGORITHMS_FOCALSEARCH_HPP
#define CUSTOMMPL_SEARCH_ALGORITHMS_FOCALSEARCH_HPP

#include "custom_mpl/search/core/result.hpp"
#include "custom_mpl/search/datastructures/open_list.hpp"
#include "custom_mpl/search/policies/closed_set.hpp"
#include "custom_mpl/search/policies/ordering.hpp"
#include "custom_mpl/search/policies/reopen.hpp"

namespace custom_mpl::search::algorithms {
template <class Node, class Graph, class IsGoalFunc, class HeuristicOpen,
          class HeuristicFocal>
core::SearchResult<Node>
focal_search(const Graph &graph, const Node &start, const IsGoalFunc &is_goal,
             const HeuristicOpen &h, const HeuristicFocal &h_f, double eps);
} // namespace custom_mpl::search::algorithms

#include "custom_mpl/search/algorithms/detail/focal_search.tpp"

#endif