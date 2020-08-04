lli f(lli x, lli c, lli mod) {
  return (mul(x, x, mod) + c) % mod;
}
 
lli rho(lli n) {
  while (1) {
    lli x = 2 + rng() % (n - 3), c = 1 + rng() % 20, y = f(x, c, n), g;
    while ((g = __gcd(n + y - x, n)) == 1)
      x = f(x, c, n), y = f(f(y, c, n), c, n);
    if (g != n) return g;
  } 
  return -1;
}
 
void pollard(lli n, map<lli, int> &fac) {
  if (n == 1) return;
  if (n % 2 == 0) {
    fac[2]++;
    pollard(n / 2, fac);
    return;
  }
  if (miller(n)) {
    fac[n]++;
    return;
  }
  lli x = rho(n);
  pollard(x, fac);
  pollard(n / x, fac);
}