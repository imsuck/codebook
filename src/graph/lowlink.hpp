/// source:
/// https://sotanishy.github.io/cp-library-cpp/graph/lowlink.hpp

void dfs(int v, int p) {
  low[v] = ord[v] = k++;
  bool is_articulation = false, checked = false;
  int cnt = 0;
  for (int c : G[v]) {
    if (c == p && !checked) {
      checked = true;
      continue;
    }
    if (ord[c] == -1) {
      ++cnt;
      dfs(c, v);
      low[v] = min(low[v], low[c]);
      if (p != -1 && ord[v] <= low[c])
        is_articulation = true;
      if (ord[v] < low[c]) bridge.push_back(minmax(v, c));
    } else {
      low[v] = min(low[v], ord[c]);
    }
  }
  if (p == -1 && cnt > 1) is_articulation = true;
  if (is_articulation) articulation.push_back(v);
}
void build() {
  for (int i = 0; i < G.size(); ++i)
    if (ord[i] == -1) dfs(i, -1);
}
bool is_bridge(int u, int v) const {
  if (ord[u] > ord[v]) swap(u, v);
  return ord[u] < low[v];
}
