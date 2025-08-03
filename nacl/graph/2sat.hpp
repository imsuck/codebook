// 0 based, vertex in SCC = MAXN * 2
struct two_SAT {
  int n, ans[MAXN];
  SCC S;
  int neg(int a) { return a < n ? a : a - n; }
  void imply(int a, int b) {
    S.make_edge(a, b), S.make_edge(neg(b), neg(a));
  }
  void add_or(int a, int b) { imply(neg(a), b); }
  void add_nand(int a, int b) { imply(a, neg(b)); }
  bool solve() {
    S.solve(n * 2);
    for (int i = 1; i <= n; i++) {
      if (S.scc[i] == S.scc[i + n]) return false;
      ans[i] = (S.scc[i] < S.scc[i + n]);
    }
    return true;
  }
  void init(int _n) {
    n = _n;
    fill_n(ans, n + 1, 0);
    S.init(n * 2);
  }
} SAT;
