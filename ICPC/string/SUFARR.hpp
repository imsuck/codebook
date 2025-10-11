void build_suf_arr() {
	for(int i = 0; i < n; ++i) ++cnt[a[i]];
	for(int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
	for(int i = 0; i < n; ++i) p[--cnt[a[i]]] = i;
	c[p[0]] = 0;
	int cls = 1;
	for(int i = 1; i < n; ++i) {
		if(a[p[i]] != a[p[i - 1]]) ++cls;
		c[p[i]] = cls - 1;
	}

	for(int k = 0; MASK32(k) < n; ++k) {
		for(int i = 0; i < n; ++i) pn[i] = (p[i] - MASK32(k) + n) % n;
		fill(cnt, cnt + cls, 0);
		for(int i = 0; i < n; ++i) ++cnt[c[pn[i]]];
		for(int i = 1; i < cls; ++i) cnt[i] += cnt[i - 1];
		for(int i = n - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];
		cn[p[0]] = 0;
		cls = 1;
		for(int i = 1; i < n; ++i) {
			pair<int, int> cur = {c[p[i]], c[(p[i] + MASK32(k)) % n]};
			pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + MASK32(k)) % n]};
			if(cur != prev) ++cls;
			cn[p[i]] = cls - 1;
		}
		for(int i = 0; i < n; ++i) c[i] = cn[i];
	}

	for(int i = 0; i < n; ++i) rnk[p[i]] = i;
	for(int i = 0, k = 0; i < n; ++i) {
		if(rnk[i] == n - 1) {
			k = 0;
			continue;
		}
		int j = p[rnk[i] + 1];
		while(i + k < n && j + k < n && a[i + k] == a[j + k]) ++k;
		lcp[rnk[i]] = k;
		if(k > 0) --k;
	}
}