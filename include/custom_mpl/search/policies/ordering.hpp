#ifndef CUSTOMMPL_SEARCH_POLICIES_ORDERING_HPP
#define CUSTOMMPL_SEARCH_POLICIES_ORDERING_HPP

#include <cstddef>

#include "custom_mpl/search/core/types.hpp"

namespace custom_mpl::search::policies {

struct AStarDeeperFirst {
  using CostType = custom_mpl::search::core::Cost;

  struct Key {
    CostType f;
    CostType g; // prefer deeper on ties
    size_t ins; // insertion order if same depth
  };

  static Key make_key(CostType g, CostType h, size_t ins) noexcept {
    return {g + h, g, ins};
  }

  struct GreaterThan {
    bool operator()(const Key &a, const Key &b) const noexcept {
      if (a.f != b.f)
        return a.f > b.f;
      if (a.g != b.g)
        return a.g < b.g;
      return a.ins > b.ins;
    }
  };
};

struct WeightedAStarLowerHFirst {
  using CostType = custom_mpl::search::core::Cost;

  double w;

  struct Key {
    CostType f;
    CostType h; // prefer lower h on ties
    size_t ins; // insertion order if same depth
  };

  Key make_key(CostType g, CostType h, size_t ins) const noexcept {
    return {g + w * h, h, ins};
  }

  struct GreaterThan {
    bool operator()(const Key &a, const Key &b) const noexcept {
      if (a.f != b.f)
        return a.f > b.f;
      if (a.h != b.h)
        return a.h > b.h;
      return a.ins > b.ins;
    }
  };
};

struct FocalHeuristicDeeperFirst {
  using CostType = custom_mpl::search::core::Cost;

  struct Key {
    CostType h_f;
    CostType g; // prefer deeper on ties
    size_t ins; // insertion order if same depth
  };

  static Key make_key(CostType g, CostType h_f, size_t ins) noexcept {
    return {h_f, g, ins};
  }

  struct GreaterThan {
    bool operator()(const Key &a, const Key &b) const noexcept {
      if (a.h_f != b.h_f)
        return a.h_f > b.h_f;
      if (a.g != b.g)
        return a.g < b.g;
      return a.ins > b.ins;
    }
  };
};

} // namespace custom_mpl::search::policies

#endif