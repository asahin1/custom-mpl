#ifndef CUSTOM_MPL_SEARCH_UTILS_HASHUTILS_HPP
#define CUSTOM_MPL_SEARCH_UTILS_HASHUTILS_HPP

#include <functional>

namespace custom_mpl::search::utils {
template <class T, class Hash = std::hash<T>> struct DerefHash {
  size_t operator()(const T *p) const noexcept { return Hash{}(*p); }
};

template <class T, class Eq = std::equal_to<T>> struct DerefEq {
  bool operator()(const T *a, const T *b) const noexcept {
    return Eq{}(*a, *b);
  }
};

} // namespace custom_mpl::search::utils

#endif