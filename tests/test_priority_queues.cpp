#include <catch2/catch_all.hpp>
#include <functional>

#include "custom_mpl/search/datastructures/pq_maker.hpp"

TEST_CASE("BinaryHeapPQ push/pop ordering") {
  using PQ = typename custom_mpl::search::datastructures::
      StdPriorityQueueMaker::template type<int, std::greater<int>>;
  PQ pq;
  pq.push(42);
  pq.push(7);
  pq.push(9);
  REQUIRE_FALSE(pq.empty());
  REQUIRE(pq.top() == 7);
  pq.pop();
  REQUIRE(pq.top() == 9);
  pq.pop();
  REQUIRE(pq.top() == 42);
  pq.pop();
  REQUIRE(pq.empty());
}
