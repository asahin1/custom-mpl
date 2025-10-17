#include <chrono>
#include <cstddef>
#include <iostream>
#include <math.h>
#include <utility>
#include <vector>

#include "custom_mpl/search/algorithms/astar.hpp"
#include "custom_mpl/search/core/heuristic.hpp"
#include "custom_mpl/search/datastructures/datastructures.hpp"
#include "custom_mpl/search/datastructures/open_list.hpp"
#include "custom_mpl/search/policies/closed_set.hpp"
#include "custom_mpl/search/policies/policies.hpp"

struct Coords {
  int x;
  int y;

  bool operator==(const Coords &other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Coords &other) const { return !operator==(other); }
};

namespace std {
template <> struct hash<Coords> {
  std::size_t operator()(const Coords &c) const noexcept {
    std::size_t h1 = std::hash<int>{}(c.x);
    std::size_t h2 = std::hash<int>{}(c.y);
    return h1 ^ (h2 << 1);
  }
};
} // namespace std

struct Obstacle {
  int x_l;
  int y_l;
  int x_u;
  int y_u;
};

struct LargeGraph {

  int x_min{0};
  int x_max{100};
  int y_min{0};
  int y_max{100};

  std::vector<Obstacle> obstacles;

  bool is_free(const Coords &n) const {
    for (const auto &obst : obstacles) {
      if (n.x > obst.x_l && n.x < obst.x_u) {
        if (n.y > obst.y_l && n.y < obst.y_u) {
          return false;
        }
      }
    }
    return true;
  }

  const std::vector<std::pair<Coords, double>>
  neighbors(const Coords &n) const {
    std::vector<std::pair<Coords, double>> res;
    Coords tn;
    for (int dx{-1}; dx < 2; ++dx) {
      for (int dy{-1}; dy < 2; ++dy) {
        if (dx == 0 && dy == 0) {
          continue;
        }
        tn.x = n.x + dx;
        tn.y = n.y + dy;
        if (!is_free(tn)) {
          continue;
        }
        double cost = sqrt(dx * dx + dy * dy);
        res.push_back({tn, cost});
      }
    }
    return res;
  }
};

int main() {
  using N = Coords;
  using G = LargeGraph;

  G graph;
  graph.obstacles.push_back({10, 10, 20, 20});
  graph.obstacles.push_back({60, 50, 80, 80});

  Coords goal{99, 99};

  auto is_goal = [&](const N &n) { return n == goal; };
  auto euclidean_heuristic = [&](const N &n) {
    return sqrt((goal.x - n.x) * (goal.x - n.x) +
                (goal.y - n.y) * (goal.y - n.y));
  };

  std::chrono::_V2::steady_clock::time_point start_time;
  std::chrono::_V2::steady_clock::time_point end_time;
  start_time = std::chrono::steady_clock::now();
  auto [res, _] = custom_mpl::search::algorithms::astar(
      graph, Coords{1, 1}, is_goal, euclidean_heuristic,
      custom_mpl::search::policies::ClosedNone{},
      custom_mpl::search::policies::ReopenForbid{});
  end_time = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff_seconds = end_time - start_time;
  double runtime = diff_seconds.count();
  std::cout << "A* found=" << res.found << " in " << runtime << " seconds. "
            << " Cost=" << res.cost << " path:";
  for (auto n : res.path)
    std::cout << " " << "(" << n.x << "," << n.y << ")";
  std::cout << "\n";

  start_time = std::chrono::steady_clock::now();
  auto res2 = custom_mpl::search::algorithms::astar_classic(
      graph, Coords{1, 1}, is_goal, euclidean_heuristic);
  end_time = std::chrono::steady_clock::now();
  diff_seconds = end_time - start_time;
  runtime = diff_seconds.count();
  std::cout << "A* (classic) found=" << res2.found << " in " << runtime
            << " seconds. "
            << " Cost=" << res2.cost << " path:";
  for (auto n : res2.path)
    std::cout << " " << "(" << n.x << "," << n.y << ")";
  std::cout << "\n";

  start_time = std::chrono::steady_clock::now();
  auto res3 = custom_mpl::search::algorithms::weighted_astar(
      graph, Coords{1, 1}, is_goal, euclidean_heuristic, 2);
  end_time = std::chrono::steady_clock::now();
  diff_seconds = end_time - start_time;
  runtime = diff_seconds.count();
  std::cout << "Weighted A* found=" << res3.found << " in " << runtime
            << " seconds. "
            << " Cost=" << res3.cost << " path:";
  for (auto n : res3.path)
    std::cout << " " << "(" << n.x << "," << n.y << ")";
  std::cout << "\n";
}