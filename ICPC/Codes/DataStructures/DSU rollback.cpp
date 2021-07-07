struct Dsu {
  vi par, tot;
  stack<ii> mem;

  Dsu(int n = 1) : par(n + 1), tot(n + 1, 1) {
    iota(all(par), 0);
  }

  int find(int u) {
    return par[u] == u ? u : find(par[u]);
  }

  void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u != v) {
      if (tot[u] < tot[v]) swap(u, v);
      mem.emplace(u, v);
      tot[u] += tot[v];
      par[v] = u;
    }
  }

  void rollback() {
    auto [u, v] = mem.top();
    mem.pop();
    if (u != -1) {
      tot[u] -= tot[v];
      par[v] = v;
    }
  }
};