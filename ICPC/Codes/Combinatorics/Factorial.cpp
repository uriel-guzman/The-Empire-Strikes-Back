fac[0] = 1LL;
fore (i, 1, N)
  fac[i] = lli(i) * fac[i - 1] % mod;
ifac[N - 1] = fpow(fac[N - 1], mod - 2);
fore (i, N - 1, 0)
  ifac[i] = lli(i + 1) * ifac[i + 1] % mod;