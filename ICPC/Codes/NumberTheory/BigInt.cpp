const int base = 1e9; 
typedef vector<lli> big;

big toBig(lli x) {
  big a;
  bool sgn = (x < 0); x = llabs(x);
  for (; x > 0; x /= base)
    a.pb(x % base);
  if (sgn)
    a.back() *= -1LL;
  return a;
}

big operator + (big a, big b) {
  big c(max(sz(a), sz(b)) + 1, 0);
  fore (i, 0, sz(c)) {
    c[i] = (i < sz(a) ? a[i]: 0) + (i < sz(b) ? b[i]: 0);
    c[i + 1] += c[i] / base;
    c[i] %= base;
  }
  if (!c.back())
    c.pop_back();
  return c;
}

big operator - (big a, big b) {
  b.back() *= -1LL;
  return a + b;
}
 
big operator * (big a, big b) {
  big c(sz(a) + sz(b), 0);
  fore (i, 0, sz(a))
    fore (j, 0, sz(b)) {
      c[i + j] += a[i] * b[j];
      c[i + j + 1] += c[i + j] / base;
      c[i + j] %= base;
    }
  if (!c.back())
    c.pop_back();
  return c;
}