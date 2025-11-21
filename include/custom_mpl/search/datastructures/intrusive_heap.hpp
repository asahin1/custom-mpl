#ifndef CUSTOMMPL_SEARCH_DATASTRUCTURES_INTRUSIVEHEAP_HPP
#define CUSTOMMPL_SEARCH_DATASTRUCTURES_INTRUSIVEHEAP_HPP

#include <cassert>
#include <cstddef>
#include <type_traits>
#include <vector>

namespace custom_mpl::search::datastructures {

template <class ItemType, class Compare> class IntrusiveHeap;

class HeapElement {
public:
  HeapElement() : heap_pos_(-1) {}

private:
  size_t heap_pos_;

  template <class ItemType, class Compare> friend class IntrusiveHeap;
};

template <class ItemType, class Compare> class IntrusiveHeap {
public:
  static_assert(std::is_base_of<HeapElement, ItemType>::value,
                "ItemType must extend HeapElement");

  IntrusiveHeap(const Compare &comp = Compare());

  size_t size() const;
  bool empty() const;
  const ItemType &top() const;
  void pop();
  void push(ItemType item);
  void erase(ItemType item);

  typename std::vector<ItemType>::const_iterator begin() const;
  typename std::vector<ItemType>::const_iterator end() const;

private:
  std::vector<ItemType> data_;
  Compare compare_;

  size_t parent(size_t i);
  size_t left(size_t i);
  size_t right(size_t i);

  void heapify(size_t i);
};

template <class ItemType, class Compare>
IntrusiveHeap<ItemType, Compare>::IntrusiveHeap(const Compare &comp)
    : compare_{comp} {}

template <class ItemType, class Compare>
size_t IntrusiveHeap<ItemType, Compare>::size() const {
  return data_.size();
}

template <class ItemType, class Compare>
bool IntrusiveHeap<ItemType, Compare>::empty() const {
  return data_.empty();
}

template <class ItemType, class Compare>
const ItemType &IntrusiveHeap<ItemType, Compare>::top() const {
  assert(!data_.empty());
  return data_.front();
}

template <class ItemType, class Compare>
void IntrusiveHeap<ItemType, Compare>::pop() {
  assert(!data_.empty());
  if (data_.size() == 1) {
    data_.pop_back();
    return;
  }
  data_.front() = std::move(data_.back());
  data_.pop_back();
  heapify(0);
}

template <class ItemType, class Compare>
void IntrusiveHeap<ItemType, Compare>::push(ItemType item) {
  data_.emplace_back(std::move(item));
  size_t i = data_.size() - 1;
  while (i != 0 && compare_(data_[parent(i)],
                            data_[i])) { // parent should come after, needs swap
    std::swap(data_[i], data_[parent(i)]);
    i = parent(i);
  }
}

template <class ItemType, class Compare>
typename std::vector<ItemType>::const_iterator
IntrusiveHeap<ItemType, Compare>::begin() const {
  return data_.begin();
}

template <class ItemType, class Compare>
typename std::vector<ItemType>::const_iterator
IntrusiveHeap<ItemType, Compare>::end() const {
  return data_.end();
}

template <class ItemType, class Compare>
inline size_t IntrusiveHeap<ItemType, Compare>::parent(size_t i) {
  return (i - 1) / 2;
}

template <class ItemType, class Compare>
inline size_t IntrusiveHeap<ItemType, Compare>::left(size_t i) {
  return 2 * i + 1;
}

template <class ItemType, class Compare>
inline size_t IntrusiveHeap<ItemType, Compare>::right(size_t i) {
  return 2 * i + 2;
}

template <class ItemType, class Compare>
void IntrusiveHeap<ItemType, Compare>::heapify(size_t i) {
  const size_t n = data_.size();
  while (true) {
    size_t l = left(i);
    size_t r = right(i);
    size_t best = i;
    if (l < n && compare_(data_[best], data_[l])) {
      best = l;
    }
    if (r < n && compare_(data_[best], data_[r])) {
      best = r;
    }
    if (best == i)
      break;
    std::swap(data_[i], data_[best]);
    i = best;
  }
}
} // namespace custom_mpl::search::datastructures

#endif