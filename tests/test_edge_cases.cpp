#include <catch2/catch_all.hpp>

#include "custom_mpl/search/algorithms/dijkstra.hpp"
#include "custom_mpl/search/datastructures/pq_binary_heap.hpp"
#include "custom_mpl/search/graphs/adjacency_list_graph.hpp"

TEST_CASE("Start equals goal") {
  using G = custom_mpl::search::graphs::AdjacencyListGraph<int>;
  using PQ = custom_mpl::search::datastructures::BinaryHeapPQ<int, double>;
  G g(1);
  auto res = custom_mpl::search::algorithms::dijkstra<int>(g, 0, 0, PQ{});
  REQUIRE(res.found);
  REQUIRE(res.cost == Catch::Approx(0.0));
  REQUIRE(res.path == std::vector<int>({0}));
}

TEST_CASE("Disconnected graph returns not found") {
  using G = custom_mpl::search::graphs::AdjacencyListGraph<int>;
  using PQ = custom_mpl::search::datastructures::BinaryHeapPQ<int, double>;
  G g(3);
  g.add_edge(0, 1, 1);
  // no path to 2
  auto res = custom_mpl::search::algorithms::dijkstra<int>(g, 0, 2, PQ{});
  REQUIRE_FALSE(res.found);
}
