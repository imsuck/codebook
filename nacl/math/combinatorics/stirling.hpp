template <class T> auto stirling1(int n) {
  vector dp(n + 1, vector<T>{});
  for (int i = 0; i <= n; ++i) {
    dp[i].resize(i + 1);
    dp[i][0] = 0, dp[i][i] = 1;
    for (int j = 1; j < i; ++j)
      dp[i][j] = dp[i - 1][j - 1] + (i - 1) * dp[i - 1][j];
  }
  return dp;
}
template <class T> auto stirling2(int n) {
  vector dp(n + 1, vector<T>{});
  for (int i = 0; i <= n; ++i) {
    dp[i].resize(i + 1);
    dp[i][0] = 0, dp[i][i] = 1;
    for (int j = 1; j < i; ++j)
      dp[i][j] = dp[i - 1][j - 1] + j * dp[i - 1][j];
  }
  return dp;
}
