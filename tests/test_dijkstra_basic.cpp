#include <catch2/catch_all.hpp>

#include "custom_mpl/search/algorithms/dijkstra.hpp"
#include "custom_mpl/search/graphs/adjacency_list_graph.hpp"

TEST_CASE("Dijkstra basic path") {
  using G = custom_mpl::search::graphs::AdjacencyListGraph<int>;
  G g(4);
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 1);
  g.add_edge(0, 2, 5);
  g.add_edge(2, 3, 1);

  auto is_goal = [](const int n) { return n == 3; };

  auto res = custom_mpl::search::algorithms::dijkstra<int>(g, 0, is_goal);
  REQUIRE(res.found);
  REQUIRE(res.cost == Catch::Approx(3.0));
  REQUIRE(res.path == std::vector<int>({0, 1, 2, 3}));
}
