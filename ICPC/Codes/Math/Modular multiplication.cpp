lli mul (lli x, lli y, lli mod) {
  lli r = 0LL;
  for (x %= mod; y > 0; y >>= 1) {
    if (y & 1) r = (r + x) % mod;
    x = (x + x) % mod;
  }
  return r;
}