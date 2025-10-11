/// src:
/// https://suisen-cp.github.io/cp-library-cpp/library/graph/functional_graph.hpp
struct Loop {
  int dist, lp_v, len;
};
template <class G> auto loops(G &f) {
  int n = f.size();
  vector<int> vis(n, n), dep(n);
  vector<Loop> res(n);
  int time = 0;
  auto dfs = [&](auto self, int v) -> int {
    vis[v] = time;
    int u = f[v];
    if (vis[u] == vis[v]) {
      int len = dep[v] - dep[u] + 1;
      res[v] = {0, v, len};
      return len - 1;
    } else if (vis[u] < vis[v]) {
      res[v] = res[u], res[v].dist++;
      return 0;
    } else {
      dep[u] = dep[v] + 1;
      int c = self(self, u);
      if (c > 0) {
        res[v] = res[u], res[v].lp_v = v;
        return c - 1;
      } else {
        res[v] = res[u], res[v].dist++;
        return 0;
      }
    }
  };
  for (int i = 0; i < n; i++, time++)
    if (vis[i] == n) dfs(dfs, i);
  return res;
}
