#ifndef CUSTOMMPL_SEARCH_DATASTRUCTURES_OPENLIST_HPP
#define CUSTOMMPL_SEARCH_DATASTRUCTURES_OPENLIST_HPP

#include <cstddef>
#include <cstdint>

#include "custom_mpl/search/datastructures/intrusive_heap.hpp"
#include "custom_mpl/search/datastructures/pq_maker.hpp"

namespace custom_mpl::search::datastructures {

template <class OrderingPolicy,
          class PQMaker =
              custom_mpl::search::datastructures::StdPriorityQueueMaker>
class OpenList {
public:
  using CostType = typename OrderingPolicy::CostType;
  using InsertionType = std::uint32_t;

  class Item : public HeapElement {
  public:
    Item(size_t id, typename OrderingPolicy::Key key, CostType g_at_push)
        : id{id}, key{key}, g_at_push{g_at_push} {}
    size_t id;
    typename OrderingPolicy::Key key;
    CostType g_at_push;
  };

  OpenList() = default;
  explicit OpenList(OrderingPolicy policy) noexcept
      : order_(std::move(policy)) {}

  const Item &top() const { return pq_.top(); }

  void push(const size_t &id, CostType g, CostType h, InsertionType ins) {
    auto key = order_.make_key(g, h, ins);
    pq_.push(Item(id, key, g));
  }
  const Item pop_min() {
    auto res = top();
    pop();
    return res;
  }

  bool empty() const { return pq_.empty(); }

  typename std::vector<Item>::const_iterator begin() const {
    return pq_.begin();
  }

  typename std::vector<Item>::const_iterator end() const { return pq_.end(); }

private:
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