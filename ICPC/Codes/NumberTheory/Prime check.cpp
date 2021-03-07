bool isPrime(lli n) {
  if (n == 1)
    return false;
  for (int pr : primes) {
    if (n % pr == 0)
      return false;
    if (1ll * pr * pr > n)
      return true;
  }
  return true;
}
