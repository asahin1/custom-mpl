#ifndef CUSTOM_MPL_SEARCH_UTILS_STATS_HPP
#define CUSTOM_MPL_SEARCH_UTILS_STATS_HPP

#include <chrono>

namespace custom_mpl::search::utils {
class Timer {
public:
  void start() { t0_ = clock::now(); }
  double seconds() const {
    return std::chrono::duration<double>(clock::now() - t0_).count();
  }

private:
  using clock = std::chrono::steady_clock;
  clock::time_point t0_ = clock::now();
};
} // namespace search::utils

#endif