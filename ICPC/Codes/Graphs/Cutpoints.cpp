int tin[N], fup[N];
int timer = 0;

void cutpoints(int u, int p = 0) {
  tin[u] = fup[u] = ++timer;
  int children = 0;
  for (int v : graph[u]) if (v != p) {
    if (!tin[v]) {
      ++children;
      cutpoints(v, u);
      fup[u] = min(fup[u], fup[v]);
      if (fup[v] >= tin[u] && p)
        // u is a cutpoint
    }
    fup[u] = min(fup[u], tin[v]);
  }
  if (!p && children > 1)
    // u is a cutpoint
}
