#ifndef SEARCH_CORE_PROBLEM_HPP
#define SEARCH_CORE_PROBLEM_HPP

#include <utility>

namespace search::core {
template <class GraphT, class NodeT, class HeuristicT> struct Problem {
  const GraphT *graph;
  NodeT start;
  NodeT goal;
  HeuristicT heuristic;

  template <class Algo, class PQ, class Key = double>
  auto solve_with(Algo &&algo, PQ pq) const {
    return algo(*graph, start, goal, heuristic, std::move(pq));
  }
};
} // namespace search::core

#endif