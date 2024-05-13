lli phi(lli n) {
  if (n == 1)
    return 0;
  lli r = n;
  for (lli i = 2; i * i <= n; i++)
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      r -= r / i;
    }
  if (n > 1)
    r -= r / n;
  return r;
}