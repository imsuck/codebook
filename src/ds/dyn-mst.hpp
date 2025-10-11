struct Edge {
  int l, r, u, v, w;
  bool operator<(const Edge &o) const { return w < o.w; }
};
struct DynamicMST {
  int n, time = 0;
  vector<array<int, 3>> init;
  vector<Edge> edges;
  vector<int> lab, lst;
  vector<int64_t> res;
  DSU dsu1, dsu2;

  DynamicMST(vector<array<int, 3>> es, int _n)
      : n(_n), init(es), lab(n), lst(es.size()), dsu1(n),
        dsu2(n) {}

  void update(int i, int nw) {
    time++;
    auto &[u, v, w] = init[i];
    edges.push_back({lst[i], time, u, v, w});
    lst[i] = time, w = nw;
  }
  void solve(int l, int r, vector<Edge> es, int cnt,
             int64_t weight) {
    auto tmp = stable_partition(all(es), [=](auto &e) {
      return !(e.r <= l || r <= e.l);
    });
    es.erase(tmp, es.end());
    dsu1.reset(cnt), dsu2.reset(cnt);

    for (auto &e : es)
      if (l < e.l || e.r < r) dsu1.merge(e.u, e.v);
    for (auto &e : es)
      if (e.l <= l && r <= e.r && dsu1.merge(e.u, e.v))
        weight += e.w, dsu2.merge(e.u, e.v);

    if (r - l == 1) return void(res[l] = weight);
    int id = 0;
    for (int i = 0; i < cnt; i++)
      if (i == dsu2.find(i)) lab[i] = id++;
    dsu1.reset(cnt);
    for (auto &e : es) {
      e.u = lab[dsu2.find(e.u)], e.v = lab[dsu2.find(e.v)];
      if (e.l <= l && r <= e.r && !dsu1.merge(e.u, e.v))
        e.r = -1;
    }
    int m = (l + r) / 2;
    solve(l, m, es, id, weight);
    solve(m, r, es, id, weight);
  }
  auto run() { // original mst weight at res[0]
    res.resize(++time);
    for (int i = 0; i < init.size(); i++) {
      auto &[u, v, w] = init[i];
      edges.push_back({lst[i], time, u, v, w});
    }
    sort(begin(edges), end(edges));
    solve(0, time, edges, n, 0);
    return res;
  }
};
