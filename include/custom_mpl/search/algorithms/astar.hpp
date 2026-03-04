#ifndef CUSTOM_MPL_SEARCH_ALGORITHMS_ASTAR_HPP
#define CUSTOM_MPL_SEARCH_ALGORITHMS_ASTAR_HPP

#include "custom_mpl/search/core/result.hpp"
#include "custom_mpl/search/datastructures/open_list.hpp"
#include "custom_mpl/search/policies/closed_set.hpp"
#include "custom_mpl/search/policies/ordering.hpp"
#include "custom_mpl/search/policies/reopen.hpp"

namespace custom_mpl::search::algorithms {

// Generalized astar to derive from
template <class Node, class Graph, class IsGoalFunc, class Heuristic,
          class PreTerminationFunc, class OrderingPolicy, class ClosedSetPolicy,
          class ReopenPolicy>
custom_mpl::search::core::SearchResult<Node> generalized_astar(
    const Graph &graph, const Node &start, const IsGoalFunc &is_goal,
    const Heuristic &h, const PreTerminationFunc &preterminate_check,
    custom_mpl::search::datastructures::OpenList<OrderingPolicy> &open,
    ClosedSetPolicy closed, ReopenPolicy reopen);
} // namespace custom_mpl::search::algorithms

#include "custom_mpl/search/algorithms/detail/astar.tpp"

namespace custom_mpl::search::algorithms {

// Regular astar (weight = 1) with deeper first tie-break
template <class Node, class Graph, class IsGoalFunc, class Heuristic,
          class PreTerminationFunc, class ClosedSetPolicy, class ReopenPolicy>
custom_mpl::search::core::SearchResult<Node>
astar(const Graph &graph, const Node &start, const IsGoalFunc &is_goal,
      const Heuristic &h, const PreTerminationFunc &preterminate_check,
      custom_mpl::search::datastructures::OpenList<
          custom_mpl::search::policies::AStarDeeperFirst> &open,
      ClosedSetPolicy closed, ReopenPolicy reopen) {
  return generalized_astar(graph, start, is_goal, h, preterminate_check, open,
                           closed, reopen);
}

// Convenience overload for returning Open List
template <class Node, class Graph, class IsGoalFunc, class Heuristic,
          class PreTerminationFunc, class ClosedSetPolicy, class ReopenPolicy>
std::pair<custom_mpl::search::core::SearchResult<Node>,
          custom_mpl::search::datastructures::OpenList<
              custom_mpl::search::policies::AStarDeeperFirst>>
astar(const Graph &graph, const Node &start, const IsGoalFunc &is_goal,
      const Heuristic &h, const PreTerminationFunc &preterminate_check,
      ClosedSetPolicy closed, ReopenPolicy reopen) {
  custom_mpl::search::datastructures::OpenList<
      custom_mpl::search::policies::AStarDeeperFirst>
      open;
  auto result =
      astar(graph, start, is_goal, h, preterminate_check, open, closed, reopen);
  return {std::move(result), std::move(open)};
}

// Regular astar (weight = 1) implementation based on Hart et al. (1968)
// Uses a closed set and nodes can be reopened
template <class Node, class Graph, class IsGoalFunc, class Heuristic>
auto astar_classic(
    const Graph &graph, const Node &start, const IsGoalFunc &is_goal,
    const Heuristic &h) { // astar implementation based on Hart et al. (1968)
  custom_mpl::search::datastructures::OpenList<
      custom_mpl::search::policies::AStarDeeperFirst>
      open;
  auto always_false = []() { return false; };
  return astar(graph, start, is_goal, h, always_false, open,
               custom_mpl::search::policies::ClosedFlag{}, // with closed list
               custom_mpl::search::policies::ReopenIfBetter{} // and reopening
  );
}

// Weighted astar with lower h first tie-break
template <class Node, class Graph, class IsGoalFunc, class Heuristic>
custom_mpl::search::core::SearchResult<Node>
weighted_astar(const Graph &graph, const Node &start, const IsGoalFunc &is_goal,
               const Heuristic &h, double weight) {
  custom_mpl::search::datastructures::OpenList open{
      custom_mpl::search::policies::WeightedAStarLowerHFirst{weight}};

  auto always_false = []() { return false; };
  return generalized_astar(
      graph, start, is_goal, h, always_false, open,
      custom_mpl::search::policies::ClosedFlag{},    // with closed list
      custom_mpl::search::policies::ReopenIfBetter{} // and reopening
  );
}

} // namespace custom_mpl::search::algorithms

#endif