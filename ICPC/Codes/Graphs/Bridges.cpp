int tin[N], fup[N];
int timer = 0;

void bridges(int u, int p = -1) {
  tin[u] = fup[u] = ++timer;
  for (int v : graph[u]) if (v != p) {
    if (!tin[v]) {
      bridges(v, u);
      fup[u] = min(fup[u], fup[v]);
      if (fup[v] > tin[u])
        // bridge u -> v
    }
    fup[u] = min(fup[u], tin[v]);
  }
}
