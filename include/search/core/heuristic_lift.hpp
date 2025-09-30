#ifndef SEARCH_CORE_HEURISTICLIFT_HPP
#define SEARCH_CORE_HEURISTICLIFT_HPP

namespace search::core {
template <class N, class H, class Indexer> struct LiftHeuristicToIds {
  const H *h;
  const Indexer *idx;
  double operator()(int a_id, int b_id) const {
    const N &a = idx->from_id(a_id);
    const N &b = idx->from_id(b_id);
    return (*h)(a, b);
  }
};
} // namespace search::core

#endif