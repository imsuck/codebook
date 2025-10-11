/// src:
/// https://www.quora.com/What-are-some-good-implementations-of-the-general-Lucas%E2%80%99-theorem-in-C++

ll crt(vector<ll> &x, vector<ll> &mod) {
  int n = x.size();
  ll M = 1;
  for (ll m : mod) M *= m;
  ll res = 0;
  for (int i = 0; i < n; i++) {
    ll out = M / mod[i];
    res += x[i] * inv(out, mod[i]) * out;
  }
  return res;
}
ll f(ll n, ll k, ll p, ll q) {
  auto fac = [](ll n, ll p, ll q) {
    ll x = 1, y = powi(p, q);
    for (int i = 2; i <= n; i++)
      if (i % p != 0) x = x * i % y;
    return x % y;
  };
  ll r = n - k, x = powi(p, q);
  ll e0 = 0, eq = 0;
  ll mul = (p == 2 && q >= 3) ? 1 : -1;
  ll cr = r, cm = k, car = 0, cnt = 0;
  while (cr || cm || car) {
    ll rr = cr % p, rm = cm % p;
    cnt++, car += rr + rm;
    if (car >= p) {
      e0++;
      if (cnt >= q) eq++;
    }
    car /= p, cr /= p, cm /= p;
  }
  mul = powi(p, e0) * powi(mul, eq);
  ll ret = (mul % x + x) % x;
  ll tmp = 1;
  for (;; tmp *= p) {
    ret = ret * fac(n / tmp % x, p, q) % x;
    ret = ret * inv(fac(n / tmp % x, p, q), x) % x;
    ret = ret * inv(fac(n / tmp % x, p, q), x) % x;
    if (tmp > n / p && tmp > k / p && tmp > r / p) break;
  }
  return (ret % x + x) % x;
}
int comb(ll n, ll k, int m) {
  int _m = m; // can use better factorization
  vector<ll> x, mod;
  for (int p = 2; p * p <= _m; p += 1 + (p & 1)) {
    if (_m % p == 0) {
      int q = 0;
      for (; _m % p == 0; _m /= p) q++;
      x.push_back(f(n, k, p, q));
      mod.push_back(powi(p, q));
    }
  }
  if (_m > 1)
    x.push_back(f(n, k, _m, 1)), mod.push_back(_m);
  return crt(x, mod) % m;
}
