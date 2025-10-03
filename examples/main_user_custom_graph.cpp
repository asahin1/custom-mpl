#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "custom_mpl/search/core/solve.hpp"
#include "custom_mpl/search/datastructures/pq_binary_heap.hpp"

struct Cell {
  int x, y;
};

bool operator==(const Cell &a, const Cell &b) {
  return a.x == b.x && a.y == b.y;
}

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

int main(int argc, char **argv) {
  int W = (argc > 1 ? std::atoi(argv[1]) : 5);
  int H = (argc > 2 ? std::atoi(argv[2]) : 4);

  MyGridGraph g{W, H};

  g.blocked.insert(Cell{1, 1});
  g.blocked.insert(Cell{2, 1});
  g.blocked.insert(Cell{1, 2});

  std::vector<Cell> all;
  all.reserve(W * H);
  for (int y = 0; y < H; ++y)
    for (int x = 0; x < W; ++x)
      if (!g.blocked.count(Cell{x, y}))
        all.push_back(Cell{x, y});

  Cell start{0, 0};
  Cell goal{W - 1, H - 1};

  auto manhattan = [](const Cell &a, const Cell &b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
  };

  auto res = custom_mpl::search::core::solve_astar_easy<Cell>(
      g, all, start, goal, manhattan,
      custom_mpl::search::datastructures::BinaryHeapPQ<int, double>{});

  if (!res.found) {
    std::cout << "No path found\n";
    return 0;
  }

  std::cout << "Cost: " << res.cost << "\nPath:";
  for (const auto &c : res.path)
    std::cout << " (" << c.x << "," << c.y << ")";
  std::cout << "\nExpanded: " << res.expanded << " Generated: " << res.generated
            << "\n";
  return 0;
}