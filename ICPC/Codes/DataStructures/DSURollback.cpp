struct Dsu {
  vector<int> pr, tot;
  stack<ii> what;

  Dsu(int n = 0) : pr(n + 5), tot(n + 5, 1) {
    iota(all(pr), 0);
  }

  int find(int u) {
    return pr[u] == u ? u : find(pr[u]);
  }

  void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v)
      what.emplace(-1, -1);
    else {
      if (tot[u] < tot[v])
        swap(u, v);
      what.emplace(u, v);
      tot[u] += tot[v];
      pr[v] = u;
    }
  }

  ii rollback() {
    ii last = what.top();
    what.pop();
    int u = last.f, v = last.s;
    if (u != -1) {
      tot[u] -= tot[v];
      pr[v] = v;
    }
    return last;
  }
};
