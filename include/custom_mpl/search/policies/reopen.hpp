#ifndef CUSTOMMPL_SEARCH_POLICIES_REOPEN_HPP
#define CUSTOMMPL_SEARCH_POLICIES_REOPEN_HPP

namespace custom_mpl::search::policies {
struct ReopenForbid {
  template <class Cost> bool should_reopen(Cost, Cost) const { return false; }
};
struct ReopenIfBetter {
  template <class Cost> bool should_reopen(Cost old_g, Cost new_g) const {
    return new_g < old_g;
  }
};
} // namespace custom_mpl::search::policies

#endif