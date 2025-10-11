void dfs(int u) {
    while(!g[u].empty()) {
        int v = g[u].back().v;
        int eid = g[u].back().eid;
        g[u].pop_back();
        if(vis[eid]) continue; // if directed graph then don't need vis
        vis[eid] = 1;
        dfs(v);
    }
    tour.push_back(u);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    int u, v;
    for(int i = 1; i <= m; ++i) {
        cin >> u >> v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
        ++deg[v];
        ++deg[u];
    }
    for(int u = 1; u <= n; ++u) {
        if(deg[u] % 2 != 0) { // if directed graph then degin[u] != degout[u]
            cout << "Not an eulerian graph";
            return 0;
        }
    }
    dfs(1);
    if(tour.size() != m + 1) cout << "Not an eulerian graph";
    else {
        cout << "Is an eulerian graph" << endl;
        for(int u : tour) cout << u << ' '; // if directed graph then need to reverse tour
    }

    return 0;
}