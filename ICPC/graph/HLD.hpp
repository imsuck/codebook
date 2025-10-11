int dfs(int u) {
    int sz = 1, mx_csz = 0;
    for(int v : g[u]) {
        if(v == par[u]) continue;
        par[v] = u;
        dep[v] = dep[u] + 1;
        int csz = dfs(v);
        sz += csz;
        if(csz > mx_csz) {
            mx_csz = csz;
            heavy[u] = v;
        }
    }
    return sz;
}
 
void hld(int u, int h, int& cur_pos) {
    head[u] = h;
    pos[u] = ++cur_pos;
    upd(1, pos[u], val[u], 1, n);
    if(heavy[u] != 0) hld(heavy[u], h, cur_pos);
    for(int v : g[u])
        if(v != par[u] && v != heavy[u]) hld(v, v, cur_pos);
}
 
long long get(int u, int v) {
    long long res = 0;
    while(head[u] != head[v]) {
        if(dep[head[u]] < dep[head[v]]) swap(u, v);
        res = max(res, get(1, pos[head[u]], pos[u], 1, n));
        u = par[head[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    res = max(res, get(1, pos[u], pos[v], 1, n));
    return res;
}