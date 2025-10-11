void dfs1(int u) {
    vis[u] = 1;
    for(int v : g[u])
        if(!vis[v]) dfs1(v);
    topo.push_back(u);
}

void dfs2(int u, int r) {
    root[u] = r;
    for(int v : g_rev[u])
        if(!root[v]) dfs2(v, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    int u, v;
    while(m--) {
        cin >> u >> v;
        g[u].push_back(v);
        g_rev[v].push_back(u);
    }
    for(int u = 1; u <= n; ++u)
        if(!vis[u]) dfs1(u);
    reverse(all(topo));
    int cnt = 0;
    for(int u : topo) {
        if(!root[u]) {
            dfs2(u, u);
            roots.push_back(u); // roots is also in topological order
            ++cnt;
        }
    }
    cout << cnt;
    for(int u = 1; u <= n; ++u) {
        for(int v : g[u])
            if(root[u] != root[v]) g_scc[root[u]].push_back(root[v]);
    }

    return 0;
}