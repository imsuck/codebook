// how many ways to divide into groups such that sum of
// max-min of each group <= x sort a increasing dp[i][j][k]
// = first i elements, j open sets, sum = k v = dp[i][j][k],
// k1 = k + j(a[i + 1] - a[i]) put a[i] in own group:
// dp[i+1][j][k1] += v put a[i] in an open group:
// dp[i+1][j][k1] += j*v put a[i] in a new group (not close
// it): dp[i+1][j+1][k1] += v put a[i] in an open group and
// close it: dp[i+1][j-1][k1] += j*v cout dp[n][0][0->x]