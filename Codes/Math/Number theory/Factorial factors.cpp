vector<ii> factorialFactors(lli n) {
  vector<ii> fac;
  for (auto p : primes) {
    if (n < p)
      break;
    lli mul = 1LL, k = 0;
    while (mul <= n / p) {
      mul *= p;
      k += n / mul;
    }
    fac.emplace_back(p, k);
  }
  return fac;
}