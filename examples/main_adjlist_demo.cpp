#include <iostream>
#include <queue>
#include <vector>

#include "custom_mpl/search/algorithms/astar.hpp"
#include "custom_mpl/search/algorithms/dijkstra.hpp"
#include "custom_mpl/search/core/types.hpp"
#include "custom_mpl/search/graphs/adjacency_list_graph.hpp"
#include "custom_mpl/search/policies/closed_set.hpp"

double heuristic(int n) {
  switch (n) {
  case 0:
    return 0;
  case 1:
    return 0;
  case 2:
    return 0;
  case 3:
    return 2;
  case 4:
    return 0;
  case 5:
    return 0;
  default:
    return 0;
  }
}

int main() {
  using N = int;
  using G = custom_mpl::search::graphs::AdjacencyListGraph<N, double>;

  G g(6);
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 1);
  g.add_edge(1, 3, 2);
  g.add_edge(2, 4, 2.5);
  g.add_edge(3, 4, 0.5);
  g.add_edge(3, 5, 2);
  g.add_edge(4, 5, 1);

  auto is_goal = [](const N &n) { return n == 5; };
  auto inconst_heuristic = [](const N &n) { return heuristic(n); };

  auto res = custom_mpl::search::algorithms::dijkstra<N>(g, 0, is_goal);
  std::cout << "Dijkstra found=" << res.found << " cost=" << res.cost
            << " path:";
  for (auto n : res.path)
    std::cout << " " << n;
  std::cout << "\n";

  auto res2 = custom_mpl::search::algorithms::astar_classic<N, G>(
      g, 0, is_goal, inconst_heuristic);
  std::cout << "A* (classic) found=" << res2.found << " cost=" << res2.cost
            << " path:";
  for (auto n : res2.path)
    std::cout << " " << n;
  std::cout << "\n";

  // A* with closed set and without node reopening: Has to result in suboptimal
  // path if the heuristic is inconsistent.
  auto [res3, open3] = custom_mpl::search::algorithms::astar<N>(
      g, 0, is_goal, heuristic, custom_mpl::search::policies::ClosedFlag{},
      custom_mpl::search::policies::ReopenForbid{});
  std::cout << "A* (classic without reopening) found=" << res3.found
            << " cost=" << res3.cost << " path:";
  for (auto n : res3.path)
    std::cout << " " << n;
  std::cout << "\n";
}