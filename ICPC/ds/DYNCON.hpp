class DSU {
  private:
	vector<ll> p, sz, sum;
	// stores all history info related to merges
	vector<pair<ll &, ll>> history;

  public:
	DSU(int n) : p(n), sz(n, 1), sum(n) { iota(p.begin(), p.end(), 0); }

	void init_sum(const vector<ll> a) {
		for (int i = 0; i < (int)a.size(); i++) { sum[i] = a[i]; }
	}

	int get(int x) { return (p[x] == x) ? x : get(p[x]); }

	ll get_sum(int x) { return sum[get(x)]; }

	void unite(int a, int b) {
		a = get(a);
		b = get(b);
		if (a == b) { return; }
		if (sz[a] < sz[b]) { swap(a, b); }

		// add to history
		history.push_back({p[b], p[b]});
		history.push_back({sz[a], sz[a]});
		history.push_back({sum[a], sum[a]});

		p[b] = a;
		sz[a] += sz[b];
		sum[a] += sum[b];
	}

	void add(int x, ll v) {
		x = get(x);
		history.push_back({sum[x], sum[x]});
		sum[x] += v;
	}

	int snapshot() { return history.size(); }

	void rollback(int until) {
		while (snapshot() > until) {
			history.back().first = history.back().second;
			history.pop_back();
		}
	}
};

const int MAXN = 3e5;

DSU dsu(MAXN);

struct Query {
	int t, u, v, x;
};

vector<Query> tree[MAXN * 4];

void update(Query &q, int v, int query_l, int query_r, int tree_l, int tree_r) {
	if (query_l > tree_r || query_r < tree_l) { return; }
	if (query_l <= tree_l && query_r >= tree_r) {
		tree[v].push_back(q);
		return;
	}
	int m = (tree_l + tree_r) / 2;
	update(q, v * 2, query_l, query_r, tree_l, m);
	update(q, v * 2 + 1, query_l, query_r, m + 1, tree_r);
}

void dfs(int v, int l, int r, vector<ll> &ans) {
	int snapshot = dsu.snapshot();
	// perform all available operations upon entering
	for (Query &q : tree[v]) {
		if (q.t == 1) { dsu.unite(q.u, q.v); }
		if (q.t == 2) { dsu.add(q.v, q.x); }
	}
	if (l == r) {
		// answer type 3 query if we have one
		for (Query &q : tree[v]) {
			if (q.t == 3) { ans[l] = dsu.get_sum(q.v); }
		}
	} else {
		// go deeper into the tree
		int m = (l + r) / 2;
		dfs(2 * v, l, m, ans);
		dfs(2 * v + 1, m + 1, r, ans);
	}
	// undo operations upon exiting
	dsu.rollback(snapshot);
}