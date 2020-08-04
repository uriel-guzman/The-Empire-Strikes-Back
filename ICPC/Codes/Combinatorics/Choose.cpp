lli choose(int n, int k) {
  if (n < 0 || k < 0 || n < k)
    return 0LL;
  return fac[n] * ifac[k] % mod * ifac[n - k] % mod;
}

lli choose(int n, int k) {
  double r = 1;
  fore (i, 1, k + 1)
    r = r * (n - k + i) / i;
  return lli(r + 0.01);
}
