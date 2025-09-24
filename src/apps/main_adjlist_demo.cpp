#include <iostream>

#include "search/algorithms/astar.hpp"
#include "search/algorithms/dijkstra.hpp"
#include "search/core/heuristic.hpp"
#include "search/datastructures/pq_binary_heap.hpp"
#include "search/graphs/adjacency_list_graph.hpp"

int main() {
  using N = int;
  using G = search::graphs::AdjacencyListGraph<N, double>;
  using PQ = search::datastructures::BinaryHeapPQ<N, double>;

  G g(4);
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 1);
  g.add_edge(0, 2, 5);
  g.add_edge(2, 3, 1);

  auto res = search::algorithms::dijkstra<N>(g, 0, 3, PQ{});
  std::cout << "Dijkstra found=" << res.found << " cost=" << res.cost
            << " path:";
  for (auto n : res.path)
    std::cout << " " << n;
  std::cout << "\n";

  auto res2 = search::algorithms::astar<N>(
      g, 0, 3, search::core::ZeroHeuristic<N>{}, PQ{});
  std::cout << "A* found=" << res2.found << " cost=" << res2.cost << " path:";
  for (auto n : res2.path)
    std::cout << " " << n;
  std::cout << "\n";
}