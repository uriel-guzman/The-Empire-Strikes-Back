vi graph[N];
int tin[N], tout[N], who[2 * N];
int timer = 0;
int n;

void dfs(int u, int p = -1) {
  tin[u] = ++timer;
  who[timer] = u;
  for (int v : graph[u])
    if (v != p)
      dfs(v, u);
  tout[u] = timer;
}
