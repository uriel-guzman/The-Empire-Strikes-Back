int tin[N], fup[N], timer = 0;

void findWeakness(int u, int p = 0) {
  tin[u] = fup[u] = ++timer;
  int children = 0;
  for (int v : graph[u]) if (v != p) {
    if (!tin[v]) {
      ++children;
      findWeakness(v, u);
      fup[u] = min(fup[u], fup[v]);
      if (fup[v] >= tin[u] && p) // u is a cutpoint
      if (fup[v] > tin[u]) // bridge u -> v
    }
    fup[u] = min(fup[u], tin[v]);
  }
  if (!p && children > 1) // u is a cutpoint
}