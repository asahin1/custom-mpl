#ifndef CUSTOM_MPL_SEARCH_GRAPHS_AUTOINTERN_HPP
#define CUSTOM_MPL_SEARCH_GRAPHS_AUTOINTERN_HPP

#include "custom_mpl/search/utils/indexer.hpp"
#include "int_adj.hpp"

namespace search::graphs {
template <class G, class N> struct AutoInterned {
  search::utils::Indexer<N> index;
  IntAdj Gid;

  template <class NodeRange> AutoInterned(const G &g, const NodeRange &nodes) {
    for (const N &n : nodes)
      (void)index.id(n);
    Gid = IntAdj(index.size());
    for (int uid = 0; uid < index.size(); ++uid) {
      const N &u = index.from_id(uid);
      for (auto &&[v, w] : g.neighbors(u)) {
        int vid = index.id(v);
        if (vid >= Gid.num_nodes())
          Gid.adj.resize(vid + 1);
        Gid.add_edge(uid, vid, w);
      }
    }
  }
};
} // namespace search::graphs

#endif