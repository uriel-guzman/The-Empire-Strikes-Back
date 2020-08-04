void add(int u, int v) {
  graph[u].pb(v);
  rgraph[v].pb(u);
}

void implication(int u, int v) {
  #define neg(u) ((n) + (u))
  add(u, v);
  add(neg(v), neg(u));
}

pair<bool, vi> satisfy(int n) {
  kosaraju(2 * n); // size of the two-sat is 2 * n 
  vi ans(n + 1, 0);
  fore (u, 1, n + 1) {
    if (scc[u] == scc[neg(u)])
      return {0, ans};
    ans[u] = scc[u] > scc[neg(u)];
  }
  return {1, ans};
}