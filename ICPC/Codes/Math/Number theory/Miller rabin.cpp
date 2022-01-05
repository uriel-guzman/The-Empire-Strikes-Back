ull mul(ull x, ull y, ull mod) {
  lli ans = x * y - mod * ull(1.L / mod * x * y);
  return ans + mod * (ans < 0) - mod * (ans >= lli(mod));
}

// use mul(x, y, mod) inside fpow
bool miller(ull n) {
  if (n < 2 || n % 6 % 4 != 1)
    return (n | 1) == 3;
  ull k = __builtin_ctzll(n - 1), d = n >> k;
  for (ull p : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
    ull x = fpow(p % n, d, n), i = k;
    while (x != 1 && x != n - 1 && p % n && i--)
      x = mul(x, x, n);
    if (x != n - 1 && i != k)
      return 0;
  }
  return 1;
}