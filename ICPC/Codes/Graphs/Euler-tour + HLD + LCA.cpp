int par[N], nxt[N], dep[N], sz[N];
int tin[N], tout[N], who[N], timer = 0;
Lazy* tree;

int dfs(int u) {
  for (auto& v : graph[u])
    if (v != par[u]) {
      par[v] = u;
      dep[v] = dep[u] + 1;
      sz[u] += dfs(v);
      if (graph[u][0] == par[u] || sz[v] > sz[graph[u][0]])
        swap(v, graph[u][0]);
    }
  return sz[u];
}

void hld(int u) {
  tin[u] = ++timer;
  who[timer] = u;
  for (auto& v : graph[u])
    if (v != par[u]) {
      nxt[v] = (v == graph[u][0] ? nxt[u] : v);
      hld(v);
    }
  tout[u] = timer;
}

template <class F>
void processPath(int u, int v, F f) {
  for (; nxt[u] != nxt[v]; u = par[nxt[u]]) {
    if (dep[nxt[u]] < dep[nxt[v]])
      swap(u, v);
    f(tin[nxt[u]], tin[u]);
  }
  if (dep[u] < dep[v])
    swap(u, v);
  f(tin[v] + overEdges, tin[u]); // overEdges???
}

void updatePath(int u, int v, lli z) {
  processPath(u, v, [&](int l, int r) {
    tree->update(l, r, z);
  });
}

void updateSubtree(int u, lli z) {
  tree->update(tin[u], tout[u], z);
}

lli queryPath(int u, int v) {
  lli sum = 0;
  processPath(u, v, [&](int l, int r) {
    sum += tree->query(l, r);
  });
  return sum;
}

lli querySubtree(int u) {
  return tree->query(tin[u], tout[u]);
}

int lca(int u, int v) {
  int last = -1;
  processPath(u, v, [&](int l, int r) {
    last = who[l];
  });
  return last;
}