ull rho(ull n) {
  auto f = [n](ull x) { return mul(x, x, n) + 1; };
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if (q = mul(prd, max(x, y) - min(x, y), n)) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}

// if used multiple times, try memorization!!
// try factoring small numbers with sieve
void pollard(ull n, map<ull, int>& fac) {
  if (n == 1) return;
  if (miller(n)) {
    fac[n]++;
  } else {
    ull x = rho(n);
    pollard(x, fac);
    pollard(n / x, fac);
  }
}