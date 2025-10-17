/// source: chatgpt x.x

long long C3(int n, const vector<pair<int, int>> &e) {
  vector<vector<int>> g(n), h(n);
  vector<int> d(n);
  for (auto [u, v] : e)
    g[u].push_back(v), g[v].push_back(u), d[u]++, d[v]++;
  for (auto [u, v] : e) {
    if (d[u] > d[v] || (d[u] == d[v] && u > v)) swap(u, v);
    h[u].push_back(v);
  }
  long long ans = 0;
  vector<int> vis(n);
  for (int u = 0; u < n; u++) {
    for (int v : h[u]) vis[v] = 1;
    for (int v : h[u])
      for (int w : h[v])
        if (vis[w]) ans++;
    for (int v : h[u]) vis[v] = 0;
  }
  return ans;
}

long long C4(int n, const vector<pair<int, int>> &e) {
  vector<vector<int>> g(n);
  for (auto [u, v] : e)
    g[u].push_back(v), g[v].push_back(u);
  vector<int> c(n);
  long long ans = 0;
  for (int u = 0; u < n; u++) {
    for (int v : g[u])
      if (v > u)
        for (int w : g[v])
          if (w > u && w != u) c[w]++;
    for (int v : g[u])
      if (v > u)
        for (int w : g[v])
          if (w > u && w != u)
            ans += 1LL * c[w] * (c[w] - 1) / 2, c[w] = 0;
  }
  return ans;
}
