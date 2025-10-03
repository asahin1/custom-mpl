#include <catch2/catch_all.hpp>

#include "custom_mpl/search/algorithms/astar.hpp"
#include "custom_mpl/search/core/heuristic.hpp"
#include "custom_mpl/search/datastructures/pq_binary_heap.hpp"
#include "custom_mpl/search/graphs/adjacency_list_graph.hpp"

TEST_CASE("A* equals Dijkstra when h=0") {
  using G = custom_mpl::search::graphs::AdjacencyListGraph<int>;
  using PQ = custom_mpl::search::datastructures::BinaryHeapPQ<int, double>;
  G g(3);
  g.add_edge(0, 1, 2);
  g.add_edge(1, 2, 2);
  g.add_edge(0, 2, 5);

  auto is_goal = [](const int n) { return n == 2; };

  auto res = custom_mpl::search::algorithms::astar_classic<int>(
      g, 0, is_goal, custom_mpl::search::core::ZeroHeuristic<int>{}, PQ{});
  REQUIRE(res.found);
  REQUIRE(res.cost == Catch::Approx(4.0));
  REQUIRE(res.path == std::vector<int>({0, 1, 2}));
}
