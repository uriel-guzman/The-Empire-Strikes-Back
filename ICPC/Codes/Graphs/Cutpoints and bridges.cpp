int tin[N], fup[N], timer = 0;

void weakness(int u, int p = -1) {
  tin[u] = fup[u] = ++timer;
  int children = 0;
  for (int v : graph[u]) if (v != p) {
    if (!tin[v]) {
      ++children;
      weakness(v, u);
      fup[u] = min(fup[u], fup[v]);
      if (fup[v] >= tin[u] && !(p == -1 && children < 2)) // u is a cutpoint
      if (fup[v] > tin[u]) // bridge u -> v
    }
    fup[u] = min(fup[u], tin[v]);
  }
}