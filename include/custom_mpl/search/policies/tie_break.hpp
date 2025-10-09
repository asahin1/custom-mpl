#ifndef CUSTOMMPL_SEARCH_POLICIES_TIEBREAK_HPP
#define CUSTOMMPL_SEARCH_POLICIES_TIEBREAK_HPP

#include "custom_mpl/search/core/types.hpp"

namespace custom_mpl::search::policies {

struct TieFGThenSeq {
  template <class Node>
  bool operator()(const custom_mpl::search::core::QItem<Node> &a,
                  const custom_mpl::search::core::QItem<Node> &b) const {
    if (a.f != b.f)
      return a.f > b.f;
    if (a.g != b.g)
      return a.g > b.g;
    return a.seq > b.seq;
  }
};
} // namespace custom_mpl::search::policies

#endif