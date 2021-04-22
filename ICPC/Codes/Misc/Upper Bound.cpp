template <class T, class F>
T upperBound(T lo, T hi, F ok) {
  while (lo + 1 < hi) {
    T mid = (lo + hi) / 2;
    if (ok(mid))
      lo = mid;
    else
      hi = mid;
  }
  return ok(hi) ? hi : ok(lo) ? lo : -1;
}