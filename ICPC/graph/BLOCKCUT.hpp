void dfs(int u, int p) {
    tin[u] = low[u] = ++timer;
    comp.push_back(u);
    for(int v : g[u]) {
        if(v == p) continue;
        if(!tin[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= tin[u]) {
                is_joint[u] = (tin[u] > 1 || tin[v] > 2);
                bccs.push_back({u});
                while(bccs.back().back() != v) {
                    bccs.back().push_back(comp.back());
                    comp.pop_back();
                }
            }
        }
        else low[u] = min(low[u], tin[v]);
    }
}
 
void build_bct() {
    int cur = 0;
    for(int u = 1; u <= n; ++u)
        if(is_joint[u]) id[u] = ++cur;
    for(const vector<int>& bcc : bccs) {
        ++cur;
        for(int u : bcc) {
            if(is_joint[u]) {
                bct[id[u]].push_back(cur);
                bct[cur].push_back(id[u]);
            }
            else id[u] = cur;
        }
    }
}