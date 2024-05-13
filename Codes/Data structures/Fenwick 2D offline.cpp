template <class T>
struct Fenwick2D { // add, build then update, query
  vector<vector<T>> fenw;
  vector<vector<int>> ys;
  vector<int> xs;
  vector<ii> pts;

  void add(int x, int y) {
    pts.pb({x, y});
  }

  void build() {
    sort(all(pts));
    for (auto&& [x, y] : pts) {
      if (xs.empty() || x != xs.back())
        xs.pb(x);
      swap(x, y);
    }
    fenw.resize(sz(xs)), ys.resize(sz(xs));
    sort(all(pts));
    for (auto&& [x, y] : pts) {
      swap(x, y);
      int i = lower_bound(all(xs), x) - xs.begin();
      for (; i < sz(fenw); i |= i + 1)
        if (ys[i].empty() || y != ys[i].back())
          ys[i].pb(y);
    }
    fore (i, 0, sz(fenw))
      fenw[i].resize(sz(ys[i]), T());
  }

  void update(int x, int y, T v) {
    int i = lower_bound(all(xs), x) - xs.begin();
    for (; i < sz(fenw); i |= i + 1) {
      int j = lower_bound(all(ys[i]), y) - ys[i].begin();
      for (; j < sz(fenw[i]); j |= j + 1) fenw[i][j] += v;
    }
  }

  T query(int x, int y) {
    T v = T();
    int i = upper_bound(all(xs), x) - xs.begin() - 1;
    for (; i >= 0; i &= i + 1, --i) {
      int j = upper_bound(all(ys[i]), y) - ys[i].begin() - 1;
      for (; j >= 0; j &= j + 1, --j) v += fenw[i][j];
    }
    return v;
  }
};