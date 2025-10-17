/// source: me?

// 0-index, half-open interval!
template <class T> struct Fenwick2DOffline {
  int n;
  vector<vector<T>> t;
  vector<vector<int>> val;

  Fenwick2DOffline() {}
  Fenwick2DOffline(int _n)
      : n(_n), t(n + 1), val(n + 1, {-1}) {}

  void add_upd(int x, int y) {
    for (x++, y++; x <= n; x += x & -x) val[x].push_back(y);
  }
  void build() {
    for (int i = 1; i <= n; i++) {
      auto &v = val[i];
      sort(begin(v), end(v));
      v.erase(unique(begin(v), end(v)), end(v));
      t[i].resize(v.size() + 1);
    }
  }
  static int idx(const vector<int> &v, int y) {
    return int(upper_bound(begin(v), end(v), y) - begin(v) -
               1);
  }
  void add(int x, int y, T d) {
    x++, y++;
    for (int i = x; i <= n; i += i & -i)
      for (int j = idx(val[i], y); j < t[i].size();
           j += j & -j)
        t[i][j] += d;
  }
  T query(int x, int y) const {
    T sum = 0;
    for (int i = x; i; i &= i - 1)
      for (int j = idx(val[i], y); j; j &= j - 1)
        sum += t[i][j];
    return sum;
  }
  T query(int x1, int y1, int x2, int y2) const {
    return query(x2, y2) - query(x1, y2) - query(x2, y1) +
           query(x1, y1);
  }
};
