template <class T>
struct Fenwick {
  vector<T> fenw;

  Fenwick(int n) : fenw(n, T()) {} // 0-indexed

  void update(int i, T v) {
    for (; i < sz(fenw); i |= i + 1)
      fenw[i] += v;
  }

  T query(int i) {
    T v = T();
    for (; i >= 0; i &= i + 1, --i)
      v += fenw[i];
    return v;
  }

  int lower_bound(T v) {
    int pos = 0;
    for (int k = __lg(sz(fenw)); k >= 0; k--)
      if (pos + (1 << k) <= sz(fenw) && fenw[pos + (1 << k) - 1] < v) {
        pos += (1 << k);
        v -= fenw[pos - 1];
      }
    return pos + (v == 0);
  }
};