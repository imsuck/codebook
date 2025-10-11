void bellman_ford(int s) {
  fill(dist + 1, dist + n + 1, inf64);
  dist[s] = 0;
  for (int i = 1; i < n; ++i) {
    for (auto [u, v, w] : g) {
      if (dist[u] != inf64 && dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        trace[v] = u;
      }
    }
  }
}

bool find_negative_cycle(vector<int> &neg_cycle) {
  // afer Bellman-Ford, this only check negative cycle in
  // the component containing the source node
  int neg_start = -1;
  for (int i = 0; i < n; ++i) {
    for (auto &[u, v, w] : g) {
      if (dist[u] != inf64 && dist[v] > dist[u] + w) {
        dist[v] = -inf64;
        trace[v] = u;
        neg_start = v;
      }
    }
  }
  if (neg_start == -1) return 0;
  int u = neg_start;
  for (int i = 0; i < n; ++i) u = trace[u];
  neg_cycle = vector<int>(1, u);
  for (int v = trace[u]; v != u; v = trace[v])
    neg_cycle.push_back(v);
  neg_cycle.push_back(u);
  reverse(all(neg_cycle));
  return 1;
}

vector<int> trace_path(int s, int u) {
  vector<int> path;
  if (dist[u] == inf64) return path;
  for (int v = u; v != 0; v = trace[v]) path.push_back(v);
  reverse(all(path));
  return path;
}