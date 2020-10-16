struct DynamicConnectivity {
  struct Query {
    int op, u, v, at;
  };

  Dsu dsu; // dsu with rollback
  vector<Query> queries;
  map<ii, int> mp;
  int timer = -1;
 
  DynamicConnectivity(int n = 0) : dsu(n) {}
 
  void add(int u, int v) {
    mp[minmax(u, v)] = ++timer;
    queries.pb({'+', u, v, INT_MAX});
  }

  void rem(int u, int v) {
    int in = mp[minmax(u, v)];
    queries.pb({'-', u, v, in});
    queries[in].at = ++timer;
    mp.erase(minmax(u, v));
  }

  void query() {
    queries.push_back({'?', -1, -1, ++timer});
  }
 
  void solve(int l, int r) {
    if (l == r) {
      if (queries[l].op == '?') // solve the query here
      return;
    }
    int m = (l + r) >> 1;
    int before = sz(dsu.mem);
    for (int i = m + 1; i <= r; i++) {
      Query &q = queries[i];
      if (q.op == '-' && q.at < l) 
        dsu.unite(q.u, q.v);
    }
    solve(l, m);
    while (sz(dsu.mem) > before) 
      dsu.rollback();
    for (int i = l; i <= m; i++) {
      Query &q = queries[i];
      if (q.op == '+' && q.at > r)
        dsu.unite(q.u, q.v);
    }
    solve(m + 1, r);
    while (sz(dsu.mem) > before)
      dsu.rollback();
  }
};
