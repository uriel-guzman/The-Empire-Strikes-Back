int par[N], dep[N], sz[N], head[N], pos[N], who[N], timer = 0;
Lazy* tree; 

int dfs(int u) {
  sz[u] = 1, head[u] = 0;
  for (int &v : graph[u]) if (v != par[u]) {
    par[v] = u;
    dep[v] = dep[u] + 1;
    sz[u] += dfs(v);
    if (graph[u][0] == par[u] || sz[v] > sz[graph[u][0]])
      swap(v, graph[u][0]); 
  }
  return sz[u];
}

void hld(int u, int h) {
  head[u] = h, pos[u] = ++timer, who[timer] = u;
  for (int &v : graph[u])
    if (v != par[u])
      hld(v, v == graph[u][0] ? h : v);
}

template <class F>
void processPath(int u, int v, F f) {
  for (; head[u] != head[v]; v = par[head[v]]) {
    if (dep[head[u]] > dep[head[v]]) swap(u, v);
    f(pos[head[v]], pos[v]);
  }
  if (dep[u] > dep[v]) swap(u, v);
  if (u != v) f(pos[graph[u][0]], pos[v]);
  f(pos[u], pos[u]); // only if hld over vertices
}

void updatePath(int u, int v, lli z) {
  processPath(u, v, [&](int l, int r) {
    tree->update(l, r, z);
  });
}

lli queryPath(int u, int v) {
  lli sum = 0;
  processPath(u, v, [&](int l, int r) {
    sum += tree->qsum(l, r);
  });
  return sum;
}
