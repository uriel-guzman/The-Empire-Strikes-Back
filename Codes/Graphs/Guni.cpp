int cnt[C], color[N];
int sz[N];

int guni(int u, int p = -1) {
  sz[u] = 1;
  for (auto& v : graph[u])
    if (v != p) {
      sz[u] += guni(v, u);
      if (sz[v] > sz[graph[u][0]] || p == graph[u][0])
        swap(v, graph[u][0]);
    }
  return sz[u];
}

void update(int u, int p, int add, bool skip) {
  cnt[color[u]] += add;
  fore (i, skip, sz(graph[u]))
    if (graph[u][i] != p)
      update(graph[u][i], u, add, 0);
}

void solve(int u, int p = -1, bool keep = 0) {
  fore (i, sz(graph[u]), 0)
    if (graph[u][i] != p)
      solve(graph[u][i], u, !i);
  update(u, p, +1, 1); // add
  // now cnt[i] has how many times the color i appears in the subtree of u
  if (!keep)
    update(u, p, -1, 0); // remove
}
