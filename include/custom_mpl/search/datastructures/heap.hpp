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
  const ItemType &top() const;
  void pop();
  void push(ItemType item);

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
const ItemType &Heap<ItemType, Compare>::top() const {
  assert(!data_.empty());
  return data_.front();
}

template <class ItemType, class Compare> void Heap<ItemType, Compare>::pop() {
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
void Heap<ItemType, Compare>::push(ItemType item) {
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
Heap<ItemType, Compare>::begin() const {
  return data_.begin();
}

template <class ItemType, class Compare>
typename std::vector<ItemType>::const_iterator
Heap<ItemType, Compare>::end() const {
  return data_.end();
}

template <class ItemType, class Compare>
inline size_t Heap<ItemType, Compare>::parent(size_t i) {
  return (i - 1) / 2;
}

template <class ItemType, class Compare>
inline size_t Heap<ItemType, Compare>::left(size_t i) {
  return 2 * i + 1;
}

template <class ItemType, class Compare>
inline size_t Heap<ItemType, Compare>::right(size_t i) {
  return 2 * i + 2;
}

template <class ItemType, class Compare>
void Heap<ItemType, Compare>::heapify(size_t i) {
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