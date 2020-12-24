int cnt[C], color[N];
int sz[N];

int guni(int u, int p = 0) { 
  sz[u] = 1; 
  for (int &v : graph[u]) if (v != p) {
    sz[u] += guni(v, u);
    if (sz[v] > sz[graph[u][0]] || p == graph[u][0])
      swap(v, graph[u][0]);
  }
  return sz[u];
}

void compute(int u, int p, int x, bool skip) {
  cnt[color[u]] += x;
  for (int i = skip; i < sz(graph[u]); i++) // don't change it with a fore!!!
    if (graph[u][i] != p)
      compute(graph[u][i], u, x, 0);
}

void solve(int u, int p, bool keep = 0) {
  fore (i, sz(graph[u]), 0)
    if (graph[u][i] != p) 
      solve(graph[u][i], u, !i);
  compute(u, p, +1, 1); // add
  // now cnt[i] has how many times the color i appears in the subtree of u
  if (!keep) compute(u, p, -1, 0); // remove
}
