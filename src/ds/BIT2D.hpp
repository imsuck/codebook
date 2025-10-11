void fakeupdate(int x, int y) {
  for (int i =
       lower_bound(a.begin(), a.end(), x) - a.begin();
       i < (int)a.size(); i += i & (-i)) {
    pos[i].push_back(y);
  }
}
void fakeget(int x, int y) {
  for (int i =
       lower_bound(a.begin(), a.end(), x) - a.begin();
       i > 0; i -= i & (-i)) {
    pos[i].push_back(y);
  }
}
void update(int x, int y, int v) {
  for (int i =
       lower_bound(a.begin(), a.end(), x) - a.begin();
       i < (int)a.size(); i += i & (-i)) {
    for (int j =
         lower_bound(pos[i].begin(), pos[i].end(), y) -
         pos[i].begin();
         j < (int)pos[i].size(); j += j & (-j)) {
      fen[i][j] = max(fen[i][j], v);
    }
  }
}
int get(int x, int y) {
  int sum = 0;
  for (int i =
       lower_bound(a.begin(), a.end(), x) - a.begin();
       i > 0; i -= i & (-i)) {
    for (int j =
         lower_bound(pos[i].begin(), pos[i].end(), y) -
         pos[i].begin();
         j > 0; j -= j & (-j)) {
      // cout << i << " " << j << " " << a[i] << ' ' <<
      // pos[i][j] << " " << fen[i][j] << "\n";
      sum = max(sum, fen[i][j]);
    }
  }
  return sum;
}