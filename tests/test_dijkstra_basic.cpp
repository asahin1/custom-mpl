#include <catch2/catch_all.hpp>

#include "search/algorithms/dijkstra.hpp"
#include "search/datastructures/pq_binary_heap.hpp"
#include "search/graphs/adjacency_list_graph.hpp"

TEST_CASE("Dijkstra basic path") {
  using G = search::graphs::AdjacencyListGraph<int>;
  using PQ = search::datastructures::BinaryHeapPQ<int, double>;
  G g(4);
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 1);
  g.add_edge(0, 2, 5);
  g.add_edge(2, 3, 1);

  auto res = search::algorithms::dijkstra<int>(g, 0, 3, PQ{});
  REQUIRE(res.found);
  REQUIRE(res.cost == Catch::Approx(3.0));
  REQUIRE(res.path == std::vector<int>({0, 1, 2, 3}));
}
