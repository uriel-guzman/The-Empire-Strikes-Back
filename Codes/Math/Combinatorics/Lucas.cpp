lli lucas(lli n, lli k) {
  if (k == 0) return 1LL;
  return lucas(n / MOD, k / MOD) * choose(n % MOD, k % MOD) % MOD;
}
