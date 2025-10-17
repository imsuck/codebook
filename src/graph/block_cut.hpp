/// source: maspy

// [0;n): original vertices
// [n;n+k): k BCCs
// (v,c): has edges from v to its biconnected component
template <typename G> auto block_cut(G &g) {
  int n = g.size();
  vector<int> low(n), ord(n), st;
  vector<bool> used(n);
  st.reserve(n);
  int nxt = n;
  int k = 0;
  vector<pair<int, int>> edges;

  auto dfs = [&](auto dfs, int v, int p) -> void {
    st.push_back(v), used[v] = 1;
    low[v] = ord[v] = k++;
    int child = 0;
    for (auto u : g[v]) {
      if (u == p) continue;
      if (!used[u]) {
        ++child;
        int s = st.size();
        dfs(dfs, u, v);
        low[v] = min(low[v], low[u]);
        if ((p == -1 && child > 1) ||
            (p != -1 && low[u] >= ord[v])) {
          edges.emplace_back(nxt, v);
          while (st.size() > s) {
            edges.emplace_back(nxt, st.back());
            st.pop_back();
          }
          ++nxt;
        }
      } else {
        low[v] = min(low[v], ord[u]);
      }
    }
  };
  for (int v = 0; v < n; v++) {
    if (used[v]) continue;
    dfs(dfs, v, -1);
    for (auto &&x : st) edges.emplace_back(nxt, x);
    ++nxt, st.clear();
  }
  vector<vector<int>> bct(nxt);
  for (auto &[u, v] : edges)
    bct[u].push_back(v), bct[v].push_back(u);
  return bct;
}
