int tin[N], fup[N];
int timer = 0;

void cutpoints(int u, int pr = 0) {
  tin[u] = fup[u] = ++timer;
  int children = 0;
  for (int v : graph[u]) if (v != pr) {
    if (!tin[v]) {
      ++children;
      cutpoints(v, u);
      fup[u] = min(fup[u], fup[v]);
      if (fup[v] >= tin[u] && pr)
        // u is a cutpoint
    }
    fup[u] = min(fup[u], tin[v]);
  }
  if (!pr && children > 1)
    // u is a cutpoint
}
