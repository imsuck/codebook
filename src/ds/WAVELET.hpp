struct Node {
  int mn, mx, lid, rid;
  vector<int> val, cnt;

  Node() : mn(inf32), mx(-inf32), lid(-1), rid(-1) {
    val.push_back(0);
    cnt.push_back(0);
  }
};
vector<Node> wavelet;

void build(int id = 0) {
  for (int i = 1; i < isz(wavelet[id].val); ++i) {
    wavelet[id].mn =
    min(wavelet[id].mn, wavelet[id].val[i]);
    wavelet[id].mx =
    max(wavelet[id].mx, wavelet[id].val[i]);
  }
  int mid = (wavelet[id].mn + wavelet[id].mx) >> 1;
  Node l, r;
  for (int i = 1; i < isz(wavelet[id].val); ++i) {
    wavelet[id].cnt.push_back(wavelet[id].cnt.back());
    if (wavelet[id].val[i] <= mid) {
      ++wavelet[id].cnt.back();
      l.val.push_back(wavelet[id].val[i]);
    } else r.val.push_back(wavelet[id].val[i]);
  }
  if (isz(wavelet[id].val) <= 2 ||
      wavelet[id].mn == wavelet[id].mx)
    return;
  if (isz(l.val) > 1) {
    wavelet[id].lid = isz(wavelet);
    wavelet.push_back(l);
    build(wavelet[id].lid);
  }
  if (isz(r.val) > 1) {
    wavelet[id].rid = isz(wavelet);
    wavelet.push_back(r);
    build(wavelet[id].rid);
  }
}

int get_kth(int id, int k, int l, int r) {
  if (id == -1 || l > r) return 0;
  if (wavelet[id].mn == wavelet[id].mx)
    return wavelet[id].mn;
  int cnt = wavelet[id].cnt[r] - wavelet[id].cnt[l - 1];
  if (cnt >= k)
    return get_kth(wavelet[id].lid, k,
                   wavelet[id].cnt[l - 1] + 1,
                   wavelet[id].cnt[r]);
  return get_kth(wavelet[id].rid, k - cnt,
                 l - wavelet[id].cnt[l - 1],
                 r - wavelet[id].cnt[r]);
}

int cnt_k(int id, int k, int l, int r) {
  if (id == -1 || l > r || wavelet[id].mx <= k) return 0;
  if (wavelet[id].mn > k) return r - l + 1;
  return cnt_k(wavelet[id].lid, k,
               wavelet[id].cnt[l - 1] + 1,
               wavelet[id].cnt[r]) +
         cnt_k(wavelet[id].rid, k,
               l - wavelet[id].cnt[l - 1],
               r - wavelet[id].cnt[r]);
}