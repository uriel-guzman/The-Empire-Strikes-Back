lli lucas(lli n, lli k) {
  if (k == 0)
    return 1LL;
  return lucas(n / mod, k / mod) * choose(n % mod, k % mod) % mod;
}