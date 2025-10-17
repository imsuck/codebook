/// source: usaco.guide + self

auto floors(ll n) {
  ll x = 1, ed;
  vector<pair<ll, ll>> res;
  for (; x <= n; x = ed) {
    ll val = n / x;
    ed = n / val + 1, res.emplace_back(val, ed - x);
  }
  return res;
}
