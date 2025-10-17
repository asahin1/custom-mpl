#ifndef CUSTOMMPL_SEARCH_DATASTRUCTURES_PQMAKER_HPP
#define CUSTOMMPL_SEARCH_DATASTRUCTURES_PQMAKER_HPP

#include <cstddef>
#include <queue>

#include "custom_mpl/search/core/types.hpp"
#include "custom_mpl/search/datastructures/heap.hpp"

namespace custom_mpl::search::datastructures {
struct StdPriorityQueueMaker {
  template <class Value, class Compare>
  using type = std::priority_queue<Value, std::vector<Value>, Compare>;
};

struct HeapMaker {
  template <class Value, class Compare>
  using type = custom_mpl::search::datastructures::Heap<Value, Compare>;
};
} // namespace custom_mpl::search::datastructures

#endif