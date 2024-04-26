struct Dsu {
  vector<int> par, tot;

  Dsu(int n = 1) : par(n + 1), tot(n + 1, 1) { iota(all(par), 0); }

  int find(int u) { return par[u] == u ? u : par[u] = find(par[u]); }

  void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u != v) {
      if (tot[u] < tot[v]) swap(u, v);

      tot[u] += tot[v];
      par[v] = u;
    }
  }
};