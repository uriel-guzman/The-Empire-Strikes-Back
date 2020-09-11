template <class T, class F = function<T(const T&, const T&)>>
struct Sparse {
  int n;
  vector<vector<T>> sp;
  F fun;

  Sparse(vector<T> &a, const F &fun) : n(sz(a)), fun(fun) {
    sp.resize(1 + __lg(n));
    sp[0] = a;
    for (int k = 1; (1 << k) <= n; k++) {
      sp[k].resize(n - (1 << k) + 1);
      fore (l, 0, n - (1 << k) + 1) {
        int r = l + (1 << (k - 1));
        sp[k][l] = fun(sp[k - 1][l], sp[k - 1][r]);
      }
    }
  }

  T get(int l, int r) {
    int k = __lg(r - l + 1);
    return fun(sp[k][l], sp[k][r - (1 << k) + 1]);
  }
};