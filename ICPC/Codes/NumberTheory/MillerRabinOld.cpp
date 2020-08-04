bool compo(lli p, lli d, lli n, lli k) { 
  lli x = fpow(p, d, n);
  while (x != 1 && x != n - 1 && p % n && k--)
    x = mul(x, x, n);
  return x != 1 && x != n - 1;
}

bool miller(lli n) {
  if (n < 2 || (n != 2 && n % 2 == 0))
    return 0;
  int k = __builtin_ctzll(n - 1);
  lli d = n >> k;
  for (lli p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == p)
      return 1;
    if (compo(p, d, n, k))
      return 0;
  }
  fore (it, 0, 20) {
    lli p = 2 + rng() % (n - 3);
    if (n == p) 
      return 1;
    if (compo(p, d, n, k))
      return 0;
  }
  return 1;
}