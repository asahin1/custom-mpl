#ifndef CUSTOMMPL_SEARCH_POLICIES_CLOSEDSET_HPP
#define CUSTOMMPL_SEARCH_POLICIES_CLOSEDSET_HPP

#include <unordered_set>

namespace custom_mpl::search::policies {
template <class N> struct ClosedSetNone {
  void clear() {}
  bool contains(const N &) const { return false; }
  void insert(const N &) {}
  void remove(const N &) {}
};

template <class N, class Hash = std::hash<N>, class Eq = std::equal_to<N>>
struct ClosedSetHash {
  std::unordered_set<N, Hash, Eq> S;
  void clear() { S.clear(); }
  bool contains(const N &n) const { return S.find(n) != S.end(); }
  void insert(const N &n) { S.insert(n); }
  void remove(const N &n) {
    auto it = S.find(n);
    if (it != S.end()) {
      S.erase(it);
    }
  }
};
} // namespace custom_mpl::search::policies

#endif