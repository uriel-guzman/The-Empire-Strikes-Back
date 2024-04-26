int par[N], depth[N], sz[N], head[N], pos[N], who[N], timer = 0;

int dfs(int u) {
  sz[u] = 1, head[u] = 0;
  for (int& v : graph[u])
    if (v != par[u]) {
      par[v] = u;
      depth[v] = depth[u] + 1;
      sz[u] += dfs(v);
      if (graph[u][0] == par[u] || sz[v] > sz[graph[u][0]])
        swap(v, graph[u][0]);
    }
  return sz[u];
}

void hld(int u, int h) {
  head[u] = h, pos[u] = ++timer, who[timer] = u;
  for (int& v : graph[u])
    if (v != par[u]) hld(v, v == graph[u][0] ? h : v);
}

template <bool OverNodes = false, class F>
void processPath(int u, int v, F f) {
  for (; head[u] != head[v]; v = par[head[v]]) {
    if (depth[head[u]] > depth[head[v]]) swap(u, v);
    f(pos[head[v]], pos[v]);
  }
  if (depth[u] > depth[v]) swap(u, v);
  if (u != v) f(pos[graph[u][0].v], pos[v]);
  if (OverNodes) f(pos[u], pos[u]); // include lca
}

void updatePath(int u, int v, lli z) {
  processPath(u, v, [&](int l, int r) { tree->update(l, r, z); });
}

lli queryPath(int u, int v) {
  lli sum = 0;
  processPath(u, v, [&](int l, int r) { sum += tree->query(l, r); });
  return sum;
}
