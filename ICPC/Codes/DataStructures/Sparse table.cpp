template <class T, class F = function<T(const T&, const T&)>>
struct Sparse {
  vector<vector<T>> sp;
  F f;
  
  Sparse(const vector<T> &a, const F &f) : sp(1 + __lg(sz(a))), f(f) {
    sp[0] = a;
    for (int k = 1; (1 << k) <= sz(a); k++) {
      sp[k].resize(sz(a) - (1 << k) + 1);
      fore (l, 0, sz(sp[k])) {
        int r = l + (1 << (k - 1));
        sp[k][l] = f(sp[k - 1][l], sp[k - 1][r]);
      }
    }
  }

  T query(int l, int r) {
    #warning Can give TLE D:, change it to a log table
    int k = __lg(r - l + 1); 
    return f(sp[k][l], sp[k][r - (1 << k) + 1]);
  }
};