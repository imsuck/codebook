struct Node {
  Node *l = 0, *r = 0;
  int val, y, c = 1;
  Node(int val) : val(val), y(rand()) {}
  void recalc();
};

int cnt(Node *n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }

template <class F> void each(Node *n, F f) {
  if (n) each(n->l, f), f(n->val), each(n->r, f);
}

pair<Node *, Node *> split(Node *n, int k) {
  if (!n) return {};
  if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
    auto [L, R] = split(n->l, k);
    n->l = R, n->recalc();
    return {L, n};
  } else {
    auto [L, R] =
    split(n->r, k - cnt(n->l) - 1); // and just "k"
    n->r = L, n->recalc();
    return {n, R};
  }
}

Node *merge(Node *l, Node *r) {
  if (!l || !r) return l ? l : r;
  if (l->y > r->y) {
    l->r = merge(l->r, r);
    return l->recalc(), l;
  } else {
    r->l = merge(l, r->l);
    return r->recalc(), r;
  }
}

Node *ins(Node *t, Node *n, int pos) {
  auto [l, r] = split(t, pos);
  return merge(merge(l, n), r);
}
