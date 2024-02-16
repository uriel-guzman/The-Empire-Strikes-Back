template <class T>
struct Seg {
  int f, n;
  vector<T> tree;

  void pull(int p) {
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
  }

  template <class Arr>
  Seg(int l, int r, Arr& a) : f(l), n(r - l + 1), tree(2 * n) {
    fore (i, 0, n)
      tree[i + n] = T(a[l + i]);
    fore (i, n, 0)
      pull(i);
  }

  template <class... Args>
  void update(int p, const Args&... args) {
    p += n - f;
    tree[p] = T(args...);
    for (int k = 1; (1 << k) <= n; k++)
      pull(p >> k);
  }

  T query(int l, int r) const {
    T pref, suf;
    for (l += n - f, r += n - f + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        pref = pref + tree[l++];
      if (r & 1)
        suf = tree[--r] + suf;
    }
    return pref + suf;
  }
};
