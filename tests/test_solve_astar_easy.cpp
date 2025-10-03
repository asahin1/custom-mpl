#include "catch2/catch_all.hpp"
#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers.hpp"

#include <cmath>
#include <cstddef>
#include <unordered_set>
#include <vector>

#include "custom_mpl/search/algorithms/astar.hpp"
#include "custom_mpl/search/core/solve.hpp"
#include "custom_mpl/search/datastructures/pq_binary_heap.hpp"

using Catch::Approx;

struct Cell {
  int x, y;
};

bool operator==(const Cell &a, const Cell &b) {
  return a.x == b.x && a.y == b.y;
}
bool operator!=(const Cell &a, const Cell &b) { return !(a == b); }
namespace std {
template <> struct hash<Cell> {
  size_t operator()(const Cell &c) const noexcept {
    return (std::hash<int>()(c.x) << 1) ^ std::hash<int>()(c.y);
  }
};
} // namespace std

struct MyGridGraph {
  int W, H;
  std::unordered_set<Cell> blocked;

  std::vector<std::pair<Cell, double>> neighbors(const Cell &u) const {
    static const int dx[4] = {1, -1, 0, 0};
    static const int dy[4] = {0, 0, 1, -1};
    std::vector<std::pair<Cell, double>> out;
    out.reserve(4);
    for (int k = 0; k < 4; ++k) {
      Cell v{u.x + dx[k], u.y + dy[k]};
      if (v.x < 0 || v.y < 0 || v.x >= W || v.y >= H)
        continue;
      if (blocked.count(v))
        continue;
      out.emplace_back(v, 1.0);
    }
    return out;
  }
};

TEST_CASE("solve_astar_easy finds shortest path on a small grid") {
  MyGridGraph g{4, 3};
  g.blocked.insert(Cell{1, 1});

  std::vector<Cell> all;
  for (int y = 0; y < g.H; ++y)
    for (int x = 0; x < g.W; ++x)
      if (!g.blocked.count(Cell{x, y}))
        all.push_back(Cell{x, y});

  Cell S{0, 0};
  Cell G{3, 2};

  auto manhattan = [](const Cell &a, const Cell &b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
  };

  auto res_easy = custom_mpl::search::core::solve_astar_easy<Cell>(
      g, all, S, G, manhattan,
      custom_mpl::search::datastructures::BinaryHeapPQ<int, double>{});

  REQUIRE(res_easy.found);
  REQUIRE(res_easy.cost == Approx(5.0));
  REQUIRE(!res_easy.path.empty());
  REQUIRE(res_easy.path.front() == S);
  REQUIRE(res_easy.path.back() == G);

  auto res_generic = custom_mpl::search::algorithms::astar<Cell>(
      g, S, G, manhattan, custom_mpl::search::datastructures::BinaryHeapPQ<Cell, double>{});

  REQUIRE(res_generic.found);
  REQUIRE(res_generic.cost == Approx(res_easy.cost));
  REQUIRE(res_generic.path.front() == res_easy.path.front());
  REQUIRE(res_generic.path.back() == res_easy.path.back());
}

TEST_CASE("solve_astar_easy handles no-path case") {
  MyGridGraph g{3, 3};
  g.blocked.insert(Cell{0, 1});
  g.blocked.insert(Cell{1, 1});
  g.blocked.insert(Cell{2, 1});

  std::vector<Cell> all;
  for (int y = 0; y < g.H; ++y)
    for (int x = 0; x < g.W; ++x)
      if (!g.blocked.count(Cell{x, y}))
        all.push_back(Cell{x, y});

  Cell S{0, 0};
  Cell G{2, 2};

  auto H = [](const Cell &a, const Cell &b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
  };

  auto res = custom_mpl::search::core::solve_astar_easy<Cell>(
      g, all, S, G, H, custom_mpl::search::datastructures::BinaryHeapPQ<int, double>{});

  REQUIRE_FALSE(res.found);
  REQUIRE(res.path.empty());
}