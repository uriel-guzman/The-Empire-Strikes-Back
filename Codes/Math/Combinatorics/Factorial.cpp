fac[0] = 1LL;
fore (i, 1, N)
  fac[i] = lli(i) * fac[i - 1] % MOD;
ifac[N - 1] = fpow(fac[N - 1], MOD - 2, MOD);
for (int i = N - 2; i >= 0; i--) ifac[i] = lli(i + 1) * ifac[i + 1] % MOD;
