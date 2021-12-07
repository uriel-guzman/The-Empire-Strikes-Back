template <class T, class F>
T lowerBound(T lo, T hi, F ok) {
  while (lo + 1 < hi) {
    T mid = (lo + hi) / 2;
    (ok(mid) ? hi : lo) = mid;
  }
  return ok(lo) ? lo : ok(hi) ? hi : -1;
}