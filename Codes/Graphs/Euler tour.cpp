int tin[N], tout[N], who[2 * N], timer = 0;

void dfs(int u, int p = -1) {
  tin[u] = ++timer, who[timer] = u;
  for (auto v : graph[u])
    if (v != p) dfs(v, u);
  tout[u] = timer;
}
