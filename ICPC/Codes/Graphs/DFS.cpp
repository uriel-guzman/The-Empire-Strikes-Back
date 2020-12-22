vector<Edge> graph[N];
bool vis[N];
int n, m;

void dfs(int u, int p = 0) {
  for (auto &e : graph[u])
    if (!vis[e.v])
      dfs(e.v, u);
}
