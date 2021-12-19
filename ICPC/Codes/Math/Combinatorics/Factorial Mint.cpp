Mint fac(int i) {
  static vector<Mint> dp(1, 1);
  while (dp.size() <= i)
    dp.pb(dp.back() * sz(dp));
  return dp[i];
}

Mint ifac(int i) {
  return fac(i).inv();
}

Mint choose(int n, int k) {
  if (n < 0 || k < 0 || n < k)
    return 0;
  return fac(n) * ifac(k) * ifac(n - k);
}
