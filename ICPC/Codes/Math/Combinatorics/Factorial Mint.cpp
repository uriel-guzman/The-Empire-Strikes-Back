Mint fac(int i) {
  static vector<Mint> dp(1, 1);
  while (dp.size() <= i)
    dp.pb(dp.back() * sz(dp));
  return dp[i];
}

Mint ifac(int i) {
  static vector<Mint> dp;
  while (dp.size() <= i)
    dp.emplace_back(fac(dp.size()).inv());
  return dp[i];
}

Mint choose(int n, int k) {
  if (n < 0 || k < 0 || n < k)
    return 0;
  return fac(n) * ifac(k) * ifac(n - k);
}
