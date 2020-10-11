struct Dsu {
  vi pr, tot;
  stack<ii> mem;

  Dsu(int n = 0) : pr(++n), tot(n, 1) {
    iota(all(pr), 0);
  }

  int find(int u) {
    return pr[u] == u ? u : find(pr[u]);
  }

  void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u != v) {
      if (tot[u] < tot[v])
        swap(u, v);
      mem.emplace(u, v);
      tot[u] += tot[v];
      pr[v] = u;
    }
  }

  void rollback() {
    auto [u, v] = mem.top();
    mem.pop();
    if (u != -1) {
      tot[u] -= tot[v];
      pr[v] = v;
    }
  }
};
