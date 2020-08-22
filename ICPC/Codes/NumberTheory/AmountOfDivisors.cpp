lli divs(lli n) {
  lli cnt = 1LL;
  for (lli p : primes) {
    if (p * p * p > n)
      break;
    if (n % p == 0) {
      lli k = 0;
      while (n > 1 && n % p == 0)
        n /= p, ++k;  
      cnt *= (k + 1);
    }
  }
  lli sq = mysqrt(n); // A binary search, the last x * x <= n
  if (miller(n))
    cnt *= 2;
  else if (sq * sq == n && miller(sq))
    cnt *= 3;
  else if (n > 1)
    cnt *= 4;
  return cnt;
}