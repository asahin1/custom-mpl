#include <catch2/catch_all.hpp>

#include "search/datastructures/pq_binary_heap.hpp"

TEST_CASE("BinaryHeapPQ push/pop ordering") {
  using PQ = search::datastructures::BinaryHeapPQ<int, double>;
  PQ pq;
  pq.push(42, 10.0);
  pq.push(7, 1.0);
  pq.push(9, 5.0);
  REQUIRE_FALSE(pq.empty());
  REQUIRE(pq.pop_min() == 7);
  REQUIRE(pq.pop_min() == 9);
  REQUIRE(pq.pop_min() == 42);
  REQUIRE(pq.empty());
}
