fac[0] = 1LL;
fore (i, 1, N)
  fac[i] = lli(i) * fac[i - 1] % mod;
ifac[n - 1] = fpow(fac[n - 1], mod - 2, mod);
for (int i = N - 1; i >= 0; i--)
  ifac[i] = lli(i + 1) * ifac[i + 1] % mod;