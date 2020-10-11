struct DynamicConnectivity {
  struct Query {
    char op;
    int u, v, out;
  };

  Dsu dsu; // dsu with rollback
  vector<Query> queries;
  vector< map<int, int> > mp;
  int timer = -1;
 
  DynamicConnectivity(int n = 0) : dsu(n), mp(n) {}
 
  void add(int u, int v) {
    if (u > v) swap(u, v);
    mp[u][v] = ++timer;
    queries.pb({'+', u, v, inf});
  }

  void rem(int u, int v) {
    if (u > v) swap(u, v);
    int in = mp[u][v];
    queries.pb({'-', u, v, in});
    queries[in].out = ++timer;
    mp[u].erase(v);
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
      if (q.out < l) 
        dsu.unite(q.u, q.v);
    }
    solve(l, m);
    while (sz(dsu.mem) > before) 
      dsu.rollback();
    for (int i = l; i <= m; i++) {
      Query &q = queries[i];
      if (q.out > r)
        dsu.unite(q.u, q.v);
    }
    solve(m + 1, r);
    while (sz(dsu.mem) > before)
      dsu.rollback();
  }
};