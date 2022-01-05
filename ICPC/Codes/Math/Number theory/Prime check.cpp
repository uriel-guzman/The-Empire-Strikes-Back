bool isPrime(lli n) {
  if (n == 1)
    return false;
  for (auto p : primes) {
    if (n % p == 0)
      return false;
    if (1LL * p * p > n)
      return true;
  }
  return true;
}
