/// source: sotanishy

long long totient(long long n) {
  long long ret = n;
  if (n % 2 == 0) {
    ret -= ret / 2;
    while (n % 2 == 0) n /= 2;
  }
  for (long long i = 3; i * i <= n; i += 2) {
    if (n % i == 0) {
      ret -= ret / i;
      while (n % i == 0) n /= i;
    }
  }
  if (n != 1) ret -= ret / n;
  return ret;
}

vector<int> totient_table(int n) {
  vector<int> ret(n + 1);
  iota(ret.begin(), ret.end(), 0);
  for (int i = 2; i <= n; ++i) {
    if (ret[i] == i)
      for (int j = i; j <= n; j += i)
        ret[j] = ret[j] / i * (i - 1);
  }
  return ret;
}
