lli fpow(lli x, lli y, lli mod) {
  lli r = 1;
  for (; y > 0; y >>= 1) {
    if (y & 1) r = mul(r, x, mod);
    x = mul(x, x, mod);
  }
  return r;
}