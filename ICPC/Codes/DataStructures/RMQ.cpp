template <class T>
struct RMQ {
  vector<vi> dp;
  vector<T> a;
  #define unite(l, r) (a[l] <= a[r] ? l : r)

  RMQ(vector<T> &a) : a(a) {
    int n = sz(a);
    fore (k, 0, 1 + __lg(n)) 
      dp.pb(vi(n - (1 << k) + 1));
    iota(all(dp[0]), 0);
    fore (k, 1, 1 + __lg(n)) 
      fore (l, 0, n - (1 << k) + 1) {
        int r = l + (1 << (k - 1));
        dp[k][l] = unite(dp[k - 1][l], dp[k - 1][r]);
      } 
  }

  int qwho(int l, int r) {
    int k = __lg(r - l + 1);
    return unite(dp[k][l], dp[k][r - (1 << k) + 1]);
  }
};
