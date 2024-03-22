lli choose(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0LL;
  return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

lli choose(int n, int k) {
  lli r = 1;
  int to = min(k, n - k);
  if (to < 0) return 0;
  fore (i, 0, to) r = r * (n - i) / (i + 1);
  return r;
}
