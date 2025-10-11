void dfs(int u) {
    tin[u] = low[u] = ++timer;
    comp.push_back(u);
    for(int i : g[u]) {
        if(vis[i]) continue;
        vis[i] = 1;
        int v = u ^ e[i].u ^ e[i].v;
        if(!tin[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
            if(low[v] == tin[v]) {
                ++bridge;
                cnt[id[v] = ++cur] = 1;
                while(comp.back() != v) {
                    ++cnt[id[comp.back()] = cur];
                    comp.pop_back();
                }
                comp.pop_back();
            }
        }
        else low[u] = min(low[u], tin[v]);
    }
    if(u == 1) {
        cnt[id[u] = ++cur] = 1;
        while(comp.back() != u) {
            ++cnt[id[comp.back()] = cur];
            comp.pop_back();
        }
        comp.pop_back();
    }
}

void build_bt() {
    for(int u = 1; u <= n; ++u) {
        for(int i : g[u]) {
            int v = u ^ e[i].u ^ e[i].v;
            if(id[u] != id[v]) bt[id[u]].push_back(id[v]);
        }
    }
}