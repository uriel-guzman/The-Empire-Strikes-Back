const int LogN = 1 + __lg(N);
int par[LogN][N], depth[N];

void dfs(int u, int par[]) {
  for (int v : graph[u])
    if (v != par[u]) {
      par[v] = u;
      depth[v] = depth[u] + 1;
      dfs(v, par);
    }
}

int lca(int u, int v){
  if (depth[u] > depth[v])
    swap(u, v);
  fore (k, LogN, 0)
    if (dep[v] - dep[u] >= (1 << k))
      v = par[k][v];
  if (u == v)
    return u;
  fore (k, LogN, 0)
    if (par[k][v] != par[k][u])
      u = par[k][u], v = par[k][v];
  return par[0][u];
}

int dist(int u, int v) {
  return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

void init(int r) {
  dfs(r, par[0]);
  fore (k, 1, LogN)
    fore (u, 1, n + 1) 	
      par[k][u] = par[k - 1][par[k - 1][u]];		
}
