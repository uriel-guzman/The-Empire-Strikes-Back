template <class T, class F>
optional<T> lowerBound(T lo, T hi, F ok) {
  while (lo + 1 < hi) {
    T mid = (lo + hi) / 2;
    (ok(mid) ? hi : lo) = mid;
  }
  return ok(lo) ? make_optional(lo) : ok(hi) ? make_optional(hi) : nullopt;
}
