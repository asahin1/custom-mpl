#include <catch2/catch_all.hpp>

#include "search/algorithms/astar.hpp"
#include "search/core/heuristic.hpp"
#include "search/datastructures/pq_binary_heap.hpp"
#include "search/graphs/adjacency_list_graph.hpp"

TEST_CASE("A* equals Dijkstra when h=0") {
  using G = search::graphs::AdjacencyListGraph<int>;
  using PQ = search::datastructures::BinaryHeapPQ<int, double>;
  G g(3);
  g.add_edge(0, 1, 2);
  g.add_edge(1, 2, 2);
  g.add_edge(0, 2, 5);

  auto res = search::algorithms::astar<int>(
      g, 0, 2, search::core::ZeroHeuristic<int>{}, PQ{});
  REQUIRE(res.found);
  REQUIRE(res.cost == Catch::Approx(4.0));
  REQUIRE(res.path == std::vector<int>({0, 1, 2}));
}
