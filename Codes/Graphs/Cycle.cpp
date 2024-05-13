bool cycle(int u) {
  vis[u] = 1;
  for (int v : graph[u]) {
    if (vis[v] == 1)
      return true;
    if (!vis[v] && cycle(v))
      return true;
  }
  vis[u] = 2;
  return false;
}