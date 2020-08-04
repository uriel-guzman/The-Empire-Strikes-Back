int scc[N], k = 0;
char vis[N];
vi order;

void dfs1(int u) {
  vis[u] = 1;
  for (int v : graph[u])
    if (vis[v] != 1)
      dfs1(v);
  order.pb(u);
}

void dfs2(int u, int k) {
  vis[u] = 2, scc[u] = k;
  for (int v : rgraph[u]) // reverse graph
    if (vis[v] != 2)
      dfs2(v, k);
}

void kosaraju() {
  fore (u, 1, n + 1)
    if (vis[u] != 1)
      dfs1(u);
  reverse(all(order));
  for (int u : order)
    if (vis[u] != 2)
      dfs2(u, ++k);
}
