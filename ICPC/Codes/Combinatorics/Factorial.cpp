void factorial(int n) {
  fac[0] = 1LL;
  fore (i, 1, n)
    fac[i] = lli(i) * fac[i - 1] % mod;
  ifac[n - 1] = fpow(fac[n - 1], mod - 2);
  fore (i, n - 1, 0)
    ifac[i] = lli(i + 1) * ifac[i + 1] % mod;
}