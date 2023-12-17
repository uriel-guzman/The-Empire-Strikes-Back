lli inv(lli a, lli m) {
  a %= m;
  assert(a);
  return a == 1 ? 1 : m - 1LL * inv(m, a) * m / a;
}