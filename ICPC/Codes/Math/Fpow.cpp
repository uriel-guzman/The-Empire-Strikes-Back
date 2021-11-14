template <class T>
T fpow(T x, lli n) {
  T r(1);
  for (; n > 0; n >>= 1) {
    if (n & 1)
      r = r * x;
    x = x * x;
  }
  return r;
}