#ifndef CUSTOMMPL_SEARCH_DATASTRUCTURES_OPENLIST_HPP
#define CUSTOMMPL_SEARCH_DATASTRUCTURES_OPENLIST_HPP

#include <cstddef>
#include <cstdint>

#include "custom_mpl/search/datastructures/pq_maker.hpp"

namespace custom_mpl::search::datastructures {

template <class OrderingPolicy,
          class PQMaker =
              custom_mpl::search::datastructures::StdPriorityQueueMaker>
class OpenList {
public:
  using CostType = typename OrderingPolicy::CostType;
  using InsertionType = std::uint32_t;

  struct Item {
    size_t id;
    typename OrderingPolicy::Key key;
    CostType g_at_push;
  };

  OpenList() = default;
  explicit OpenList(OrderingPolicy policy) noexcept
      : order_(std::move(policy)) {}

  void push(size_t &id, CostType g, CostType h, InsertionType ins) {
    auto key = order_.make_key(g, h, ins);
    pq_.emplace(Item{id, key, g});
  }
  const Item pop_min() {
    auto res = top();
    pop();
    return res;
  }

  bool empty() const { return pq_.empty(); }

private:
  const Item &top() const { return pq_.top(); }
  void pop() noexcept { pq_.pop(); }

  struct Cmp {
    bool operator()(const Item &a, const Item &b) const noexcept {
      return typename OrderingPolicy::GreaterThan{}(a.key, b.key);
    }
  };

  using PQ = typename PQMaker::template type<Item, Cmp>;
  PQ pq_;
  OrderingPolicy order_{};
};
} // namespace custom_mpl::search::datastructures

#endif