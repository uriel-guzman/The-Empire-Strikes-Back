int pr[N], dep[N], sz[N], heavy[N], head[N], pos[N], who[N], timer = 0;
Lazy* tree; // generally a lazy segtree

int dfs(int u) {
  sz[u] = 1, heavy[u] = head[u] = 0;
  for (int v : graph[u]) if (v != pr[u]) {
    pr[v] = u;
    dep[v] = dep[u] + 1;
    sz[u] += dfs(v);
    if (sz[v] > sz[heavy[u]])
      heavy[u] = v;
  }
  return sz[u];
}

void hld(int u, int h) {
  head[u] = h, pos[u] = ++timer, who[timer] = u;
  if (heavy[u] != 0)
    hld(heavy[u], h);
  for (int v : graph[u])
    if (v != pr[u] && v != heavy[u])
      hld(v, v);
}

template <class F>
void processPath(int u, int v, F fun) {
  for (; head[u] != head[v]; v = pr[head[v]]) {
    if (dep[head[u]] > dep[head[v]]) 
      swap(u, v);
    fun(pos[head[v]], pos[v]);
  }
  if (dep[u] > dep[v]) 
    swap(u, v);
  if (u != v) 
    fun(pos[heavy[u]], pos[v]);
  fun(pos[u], pos[u]); // process lca(u, v) too?
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