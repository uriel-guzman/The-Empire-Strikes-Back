int tin[N], tout[N], who[N], sz[N], heavy[N], color[N];
int timer = 0;

int dfs(int u, int pr = 0){
  sz[u] = 1;
  tin[u] = ++timer, who[timer] = u;
  for (int v : graph[u]) if (v != pr) {
    sz[u] += dfs(v, u);
    if (sz[v] > sz[heavy[u]])
      heavy[u] = v;
  }
  tout[u] = timer;
  return sz[u];
}

void guni(int u, int pr = 0, bool keep = 0) {
  for (int v : graph[u])
    if (v != pr && v != heavy[u])
      guni(v, u, 0);
  if (heavy[u])
    guni(heavy[u], u, 1);
  for (int v : graph[u])
    if (v != pr && v != heavy[u])
      fore (i, tin[v], tout[v] + 1)
        add(color[who[i]]);
  add(color[u]);
  for (Query &q : queries[u])
    ans[q.i] = sum;
  if (keep == 0)
    fore (i, tin[u], tout[u] + 1)
      rem(color[who[i]]);
}
