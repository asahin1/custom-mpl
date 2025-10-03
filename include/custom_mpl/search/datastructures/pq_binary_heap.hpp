#ifndef CUSTOM_MPL_SEARCH_DATASTRUCTURES_PQBINARYHEAP_HPP
#define CUSTOM_MPL_SEARCH_DATASTRUCTURES_PQBINARYHEAP_HPP

#include <cstddef>
#include <functional>
#include <iterator>
#include <queue>
#include <utility>
#include <vector>

namespace search::datastructures {
template <class Node, class Key = double> class BinaryHeapPQ {
  struct Item {
    Key key;
    std::size_t seq;
    Node node;
  };
  struct Cmp {
    bool operator()(const Item &a, const Item &b) const {
      if (a.key != b.key)
        return a.key > b.key;
      return a.seq > b.seq;
    }
  };
  std::priority_queue<Item, std::vector<Item>, Cmp> q_;
  std::size_t next_seq_ = 0;

public:
  static constexpr bool supports_decrease_key = false;

  void push(const Node &n, const Key &k) { q_.push(Item{k, next_seq_++, n}); }
  Node pop_min() {
    auto n = q_.top().node;
    q_.pop();
    return n;
  }
  bool empty() const { return q_.empty(); }
  std::size_t size() const { return q_.size(); }
};
} // namespace search::datastructures

#endif