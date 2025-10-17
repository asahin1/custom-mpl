#ifndef CUSTOMMPL_SEARCH_POLICIES_CLOSEDSET_HPP
#define CUSTOMMPL_SEARCH_POLICIES_CLOSEDSET_HPP

#include <cassert>
#include <cstddef>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace custom_mpl::search::policies {
struct ClosedNone {
  bool is_closed(const bool &flag) const { return false; }
  void mark_closed(bool &flag) const {}
  void reopen(bool &flag) const {}
  static constexpr bool gates_enqueue = false;
};
struct ClosedFlag {
  static constexpr bool gates_enqueue = true;
  bool is_closed(const bool &flag) const { return flag; }
  void mark_closed(bool &flag) const { flag = true; }
  void reopen(bool &flag) const { flag = false; }
};
} // namespace custom_mpl::search::policies

#endif