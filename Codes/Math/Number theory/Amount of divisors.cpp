ull amountOfDivisors(ull n) {
  ull cnt = 1;
  for (auto p : primes) {
    if (1LL * p * p * p > n)
      break;
    if (n % p == 0) {
      ull k = 0;
      while (n > 1 && n % p == 0) n /= p, ++k;
      cnt *= (k + 1);
    }
  }
  ull sq = mysqrt(n); // the last x * x <= n
  if (miller(n))
    cnt *= 2;
  else if (sq * sq == n && miller(sq))
    cnt *= 3;
  else if (n > 1)
    cnt *= 4;
  return cnt;
}