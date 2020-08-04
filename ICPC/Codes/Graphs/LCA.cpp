const int LogN = 1 + __lg(N);
int pr[LogN][N], dep[N];

void dfs(int u, int pr[]) {
  for (int v : graph[u])
    if (v != pr[u]) {
      pr[v] = u;
      dep[v] = dep[u] + 1;
      dfs(v, pr);
    }
}

int lca(int u, int v){
  if (dep[u] > dep[v])
    swap(u, v);
  fore (k, LogN, 0)
    if (dep[v] - dep[u] >= (1 << k))
      v = pr[k][v];
  if (u == v)
    return u;
  fore (k, LogN, 0)
    if (pr[k][v] != pr[k][u])
      u = pr[k][u], v = pr[k][v];
  return pr[0][u];
}

int dist(int u, int v) {
  return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

void init(int r) {
  dfs(r, pr[0]);
  fore (k, 1, LogN)
    fore (u, 1, n + 1) 	
      pr[k][u] = pr[k - 1][pr[k - 1][u]];		
}
