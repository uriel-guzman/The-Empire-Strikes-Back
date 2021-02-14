map<int, int> factorize(lli n) {
  map<int, int> f;

  for (int pr : primes) {
    if (pr > n)
      break;
    while (n % pr == 0) {
      f[pr]++;
      n /= pr;
    }
  }

  if (n > 1)
    f[n]++;

  return f;
}
