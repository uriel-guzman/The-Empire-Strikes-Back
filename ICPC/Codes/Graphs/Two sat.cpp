// 1-indexed
struct TwoSat {
  int n;
  vector<vector<int>> imp;

  TwoSat(int k) : n(k + 1), imp(2 * n) {}

  // a || b
  void either(int a, int b) {
    a = max(2 * a, -1 - 2 * a);
    b = max(2 * b, -1 - 2 * b);
    imp[a ^ 1].pb(b);
    imp[b ^ 1].pb(a);
  }

  // if a then b
  // a  b   a => b
  // F  F     T
  // T  T     T
  // F  T     T
  // T  F     F
  void implies(int a, int b) {
    either(~a, b);
  }

  // setVal(a): set a = true
  // setVal(~a): set a = false
  void setVal(int a) {
    either(a, a);
  }

  optional<vector<int>> solve() {
    int k = sz(imp);
    vector<int> s, b, id(sz(imp));

    function<void(int)> dfs = [&](int u) {
      b.pb(id[u] = sz(s)), s.pb(u);
      for (int v : imp[u]) {
        if (!id[v])
          dfs(v);
        else
          while (id[v] < b.back())
            b.pop_back();
      }
      if (id[u] == b.back())
        for (b.pop_back(), ++k; id[u] < sz(s); s.pop_back())
          id[s.back()] = k;
    };

    vector<int> val(n);
    fore (u, 0, sz(imp))
      if (!id[u])
        dfs(u);
    fore (u, 0, n) {
      int x = 2 * u;
      if (id[x] == id[x ^ 1])
        return nullopt;
      val[u] = id[x] < id[x ^ 1];
    }
    return optional(val);
  }
};
