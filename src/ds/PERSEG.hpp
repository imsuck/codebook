struct Node {
  int id, lid, rid, sum;

  Node() : id(-1), lid(-1), rid(-1), sum(0) {}

  Node(int v) : id(-1), lid(-1), rid(-1), sum(v) {}

  Node(const Node &l, const Node &r)
      : id(-1), lid(l.id), rid(r.id), sum(0) {
    if (l.id != -1) sum += l.sum;
    if (r.id != -1) sum += r.sum;
  }
};
vector<Node> seg;
vector<int> roots;

int build(int l, int r) {
  if (l == r) {
    seg.push_back(Node(0));
    seg.back().id = isz(seg) - 1;
    return seg.back().id;
  }
  int mid = (l + r) >> 1;
  int lid = build(l, mid), rid = build(mid + 1, r);
  seg.push_back(Node(seg[lid], seg[rid]));
  seg.back().id = isz(seg) - 1;
  return seg.back().id;
}

int upd(int id, int i, int l, int r) {
  if (l == r) {
    seg.push_back(Node(seg[id].sum + 1));
    seg.back().id = isz(seg) - 1;
    return seg.back().id;
  }
  int mid = (l + r) >> 1;
  int lid, rid;
  if (i <= mid)
    lid = upd(seg[id].lid, i, l, mid), rid = seg[id].rid;
  else
    lid = seg[id].lid,
    rid = upd(seg[id].rid, i, mid + 1, r);
  seg.push_back(Node(seg[lid], seg[rid]));
  seg.back().id = isz(seg) - 1;
  return seg.back().id;
}

int get_kth(int idl, int idr, int k, int l, int r) {
  if (l == r) return l;
  int mid = (l + r) >> 1;
  int cnt = seg[seg[idr].lid].sum - seg[seg[idl].lid].sum;
  if (cnt >= k)
    return get_kth(seg[idl].lid, seg[idr].lid, k, l, mid);
  return get_kth(seg[idl].rid, seg[idr].rid, k - cnt,
                 mid + 1, r);
}

int cnt_k(int idl, int idr, int k, int l, int r) {
  if (r <= k) return 0;
  if (l > k) return seg[idr].sum - seg[idl].sum;
  int mid = (l + r) >> 1;
  return cnt_k(seg[idl].lid, seg[idr].lid, k, l, mid) +
         cnt_k(seg[idl].rid, seg[idr].rid, k, mid + 1, r);
}