lli hilbert(int x, int y, int pw = 21, int rot = 0) {
  if (pw == 0)
    return 0;
  int hpw = 1 << (pw - 1);
  int k = ((x < hpw ? y < hpw ? 0 : 3 : y < hpw ? 1 : 2) + rot) & 3;
  const int d[4] = {3, 0, 0, 1};
  lli a = 1LL << ((pw << 1) - 2);
  lli b = hilbert(x & (x ^ hpw), y & (y ^ hpw), pw - 1, (rot + d[k]) & 3);
  return k * a + (d[k] ? a - b - 1 : b);
}