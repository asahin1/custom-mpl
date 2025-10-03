#ifndef CUSTOM_MPL_SEARCH_UTILS_INDEXER_HPP
#define CUSTOM_MPL_SEARCH_UTILS_INDEXER_HPP

#include <unordered_map>
#include <vector>

namespace custom_mpl::search::utils {
template <class N> class Indexer {
public:
  int id(const N &n) {
    auto it = to_id_.find(n);
    if (it != to_id_.end())
      return it->second;
    int nid = static_cast<int>(from_id_.size());
    to_id_.emplace(n, nid);
    from_id_.push_back(n);
    return nid;
  }
  const N &from_id(int nid) const { return from_id_[nid]; }
  int size() const { return static_cast<int>(from_id_.size()); }

private:
  std::unordered_map<N, int> to_id_;
  std::vector<N> from_id_;
};
} // namespace search::utils

#endif