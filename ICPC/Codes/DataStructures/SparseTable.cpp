template <class T, class F = function<T(const T&, const T&)>>
struct Sparse {
  int n;
  vector<vector<T>> sp;
  F f;

  Sparse(vector<T> &a, const F &f) : n(sz(a)), sp(1 + __lg(n)), f(f) {
    sp[0] = a;
    for (int k = 1; (1 << k) <= n; k++) {
      sp[k].resize(n - (1 << k) + 1);
      fore (l, 0, sz(sp[k])) {
        int r = l + (1 << (k - 1));
        sp[k][l] = f(sp[k - 1][l], sp[k - 1][r]);
      }
    }
  }

  T query(int l, int r) {
    int k = __lg(r - l + 1);
    return f(sp[k][l], sp[k][r - (1 << k) + 1]);
  }
};