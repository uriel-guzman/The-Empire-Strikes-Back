template <class T>
struct Fenwick {
  #define lsb(x) (x & -x)
  vector<T> fenw;

  Fenwick(int n = 1) : fenw(n + 1, {}) {}

  void update(int i, T v) {
    for (; i < sz(fenw); i += lsb(i))
      fenw[i] += v;
  }

  T query(int i) {
    T v = {};
    for (; i > 0; i -= lsb(i))
      v += fenw[i];
    return v;
  }

  int lower_bound(T v) {
    int i = 0;
    fore (k, 1 + __lg(sz(fenw)), 0)
      if (i + (1 << k) < sz(fenw) && v - fenw[i + (1 << k)] > 0) {
        i += (1 << k);
        v -= fenw[i];
      }
    return i + 1;
  }
};