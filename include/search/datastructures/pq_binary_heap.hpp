#ifndef SEARCH_DATASTRUCTURES_PQBINARYHEAP_HPP
#define SEARCH_DATASTRUCTURES_PQBINARYHEAP_HPP

#include <cstddef>
#include <functional>
#include <iterator>
#include <queue>
#include <utility>
#include <vector>

namespace search::datastructures {
template <class Node, class Key = double> class BinaryHeapPQ {
  using Item = std::pair<Key, Node>;
  std::priority_queue<Item, std::vector<Item>, std::greater<Item>> q_;

public:
  static constexpr bool supports_decrease_key = false;
  void push(const Node &n, const Key &k) { q_.emplace(k, n); }
  Node pop_min() {
    auto n = q_.top().second;
    q_.pop();
    return n;
  }
  bool empty() const { return q_.empty(); }
  std::size_t size() const { return q_.size(); }
};
} // namespace search::datastructures

#endif