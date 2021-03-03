map<int, int> factorize(lli n) {
  map<int, int> cnt;
  for (int p : primes) {
    if (p > n)
      break;
    while (n % p == 0) {
      cnt[p]++;
      n /= p;
    }
  }
  if (n > 1)
    cnt[n]++;
  return cnt;
}
