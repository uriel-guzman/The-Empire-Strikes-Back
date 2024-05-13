ull mul(ull x, ull y, ull MOD) {
  lli ans = x * y - MOD * ull(1.L / MOD * x * y);
  return ans + MOD * (ans < 0) - MOD * (ans >= lli(MOD));
}

// use mul(x, y, mod) inside fpow
bool miller(ull n) {
  if (n < 2 || n % 6 % 4 != 1)
    return (n | 1) == 3;
  ull k = __builtin_ctzll(n - 1), d = n >> k;
  for (ull p : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
    ull x = fpow(p % n, d, n), i = k;
    while (x != 1 && x != n - 1 && p % n && i--) x = mul(x, x, n);
    if (x != n - 1 && i != k)
      return 0;
  }
  return 1;
}
