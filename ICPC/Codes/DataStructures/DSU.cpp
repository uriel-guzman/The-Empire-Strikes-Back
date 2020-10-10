struct Dsu {
  vi pr;

  Dsu(int n = 0) : pr(++n) {
    iota(all(pr), 0);
  }

  int find(int u) {
    return pr[u] == u ? u : pr[u] = find(pr[u]);
  }

  void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u != v)
      pr[v] = u;
  }
};
