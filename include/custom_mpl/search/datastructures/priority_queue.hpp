#ifndef CUSTOMMPL_SEARCH_DATASTRUCTURES_PRIORITYQUEUE_HPP
#define CUSTOMMPL_SEARCH_DATASTRUCTURES_PRIORITYQUEUE_HPP

#include <cstddef>

#include "custom_mpl/search/core/types.hpp"

namespace custom_mpl::search::datastructures {
template <class Node, class Container> class PriorityQueue {
  Container q_;

public:
  static constexpr bool supports_decrease_key = false;

  void push(const Node &n, const custom_mpl::search::core::Cost &f,
            const custom_mpl::search::core::Cost &g, const size_t &seq) {
    q_.push(custom_mpl::search::core::QItem<Node>{n, f, g, seq});
  }
  Node pop_min() {
    auto n = q_.top().node;
    q_.pop();
    return n;
  }
  bool empty() const { return q_.empty(); }
  std::size_t size() const { return q_.size(); }
};
} // namespace custom_mpl::search::datastructures

#endif