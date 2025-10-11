/// source: sotanishy

int mobius(long long n) {
  long long ret = 1;
  if (n % 4 == 0) return 0;
  if (n % 2 == 0) ret *= -1, n /= 2;
  for (long long i = 3; i * i <= n; i += 2) {
    if (n % (i * i) == 0) return 0;
    if (n % i == 0) ret *= -1, ret /= i;
  }
  if (n != 1) ret *= -1;
  return ret;
}
vector<int> mobius_table(int n) {
  vector<bool> prime(n + 1, true);
  vector<int> ret(n + 1, 1);
  for (int i = 2; i <= n; ++i) {
    if (!prime[i]) continue;
    for (int j = i; j <= n; j += i) {
      if (j > i) prime[j] = false;
      if ((j / i) % i == 0) ret[j] = 0;
      else ret[j] *= -1;
    }
  }
  return ret;
}
