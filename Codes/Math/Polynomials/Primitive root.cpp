int primitive(int p) {
  auto fpow = [&](lli x, int n) {
    lli r = 1;
    for (; n > 0; n >>= 1) {
      if (n & 1) r = r * x % p;
      x = x * x % p;
    }
    return r;
  };

  for (int g = 2; g < p; g++) {
    bool can = true;
    for (int i = 2; i * i < p; i++)
      if ((p - 1) % i == 0) {
        if (fpow(g, i) == 1) can = false;
        if (fpow(g, (p - 1) / i) == 1) can = false;
      }
    if (can) return g;
  }
  return -1;
}