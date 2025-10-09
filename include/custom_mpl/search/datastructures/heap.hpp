#ifndef CUSTOMMPL_SEARCH_DATASTRUCTURES_HEAP_HPP
#define CUSTOMMPL_SEARCH_DATASTRUCTURES_HEAP_HPP

#include <cassert>
#include <cstddef>
#include <vector>

namespace custom_mpl::search::datastructures {
template <class ItemType, class Compare> class Heap {
public:
  Heap(const Compare &comp = Compare());

  size_t size() const;
  bool empty() const;
  const ItemType top() const;
  void pop();
  void push(ItemType item);

private:
  std::vector<ItemType> data_;
  Compare compare_;

  size_t parent(size_t i);
  size_t left(size_t i);
  size_t right(size_t i);

  void min_heapify(size_t i);
  void swap(ItemType &t1, ItemType &t2);
};

template <class ItemType, class Compare>
Heap<ItemType, Compare>::Heap(const Compare &comp) : compare_{comp} {}

template <class ItemType, class Compare>
size_t Heap<ItemType, Compare>::size() const {
  return data_.size();
}

template <class ItemType, class Compare>
bool Heap<ItemType, Compare>::empty() const {
  return data_.empty();
}

template <class ItemType, class Compare>
const ItemType Heap<ItemType, Compare>::top() const {
  assert(!data_.empty());
  return data_.front();
}

template <class ItemType, class Compare> void Heap<ItemType, Compare>::pop() {
  assert(!data_.empty());
  data_[0] = data_[data_.size() - 1];
  data_.pop_back();
  min_heapify(0);
}

template <class ItemType, class Compare>
void Heap<ItemType, Compare>::push(ItemType item) {
  data_.emplace_back(item);
  size_t i = data_.size() - 1;
  while (i != 0 && !compare_(data_[parent(i)], data_[i])) {
    swap(data_[i], data_[parent(i)]);
    i = parent(i);
  }
}

template <class ItemType, class Compare>
inline size_t Heap<ItemType, Compare>::parent(size_t i) {
  return i >> 1;
}

template <class ItemType, class Compare>
inline size_t Heap<ItemType, Compare>::left(size_t i) {
  return i << 1;
}

template <class ItemType, class Compare>
inline size_t Heap<ItemType, Compare>::right(size_t i) {
  return (i << 1) + 1;
}

template <class ItemType, class Compare>
void Heap<ItemType, Compare>::min_heapify(size_t i) {
  size_t l = left(i);
  size_t r = right(i);
  size_t smallest = i;

  if (l < data_.size() && compare_(data_[l], data_[i])) {
    smallest = l;
  }
  if (r < data_.size() && compare_(data_[r], data_[i])) {
    smallest = r;
  }
  if (smallest != i) {
    swap(data_[i], data_[smallest]);
    min_heapify(smallest);
  }
}

template <class ItemType, class Compare>
void Heap<ItemType, Compare>::swap(ItemType &t1, ItemType &t2) {
  ItemType temp = t1;
  t1 = t2;
  t2 = temp;
}

} // namespace custom_mpl::search::datastructures

#endif