template <class T>
struct Fenwick2D {
  vector<vector<T>> fenw;
  vector<vi> mp;

  Fenwick2D(int n = 1) : mp(n), fenw(n) {}

  void build() {
    for (auto &v : mp) {
      sort(all(v));
      v.erase(unique(all(v)), v.end());
      fenw[&v - &mp[0]].resize(sz(v));
    } 
  }

  void add(int x, int y) {
    for (; x < sz(fenw); x |= x + 1) 
      mp[x].pb(y);
  }

  void update(int x, int y, T v) {
    for (; x < sz(fenw); x |= x + 1) {
      int i = lower_bound(all(mp[x]), y) - mp[x].begin();
      for (; i < sz(fenw[x]); i |= i + 1)
        fenw[x][i] += v;
    }
  }

  T query(int x, int y) {
    T v = 0;
    for (; x >= 0; x &= x + 1, --x) {
      int i = upper_bound(all(mp[x]), y) - mp[x].begin() - 1;
      for (; i >= 0; i &= i + 1, --i)
        v += fenw[x][i];
    }
    return v;
  }
};