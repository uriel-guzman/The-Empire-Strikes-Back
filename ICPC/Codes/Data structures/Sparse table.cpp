template <class T, class F = function<T(const T&, const T&)>>
struct Sparse {
  vector<T> sp[21]; // n <= 2^21
  F f;
  int n;

  Sparse(T* begin, T* end, const F& f) : Sparse(vector<T>(begin, end), f) {}

  Sparse(const vector<T>& a, const F& f) : f(f), n(sz(a)) {
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
#warning Can give TLE D:, change it to a log table
    int k = __lg(r - l + 1);
    return f(sp[k][l], sp[k][r - (1 << k) + 1]);
  }

  T queryBits(int l, int r) {
    optional<T> ans;
    for (int len = r - l + 1; len; len -= len & -len) {
      int k = __builtin_ctz(len);
      ans = ans ? f(ans.value(), sp[k][l]) : sp[k][l];
      l += (1 << k);
    }
    return ans.value();
  }
};