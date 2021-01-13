bool miller(lli n) {
  if (n < 2 || n % 6 % 4 != 1)
    return (n | 1) == 3;
  int k = __builtin_ctzll(n - 1);
  lli d = n >> k;
  auto compo = [&](lli p) { 
    lli x = fpow(p % n, d, n), i = k;
    while (x != 1 && x != n - 1 && p % n && i--)
      x = mul(x, x, n);
    return x != n - 1 && i != k;
  };
  for (lli p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (compo(p))
      return 0;
    if (compo(2 + rng() % (n - 3)))
      return 0;
  }
  return 1;
}
