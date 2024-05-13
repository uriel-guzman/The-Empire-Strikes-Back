lli facMod(lli n, int p) {
  lli r = 1LL;
  for (; n > 1; n /= p) {
    r = (r * ((n / p) % 2 ? p - 1 : 1)) % p;
    fore (i, 2, n % p + 1)
      r = r * i % p;
  }
  return r % p;
}
