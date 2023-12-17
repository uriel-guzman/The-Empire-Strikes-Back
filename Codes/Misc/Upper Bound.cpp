template <class T, class F>
optional<T> upperBound(T lo, T hi, F ok) {
  while (lo + 1 < hi) {
    T mid = (lo + hi) / 2;
    (ok(mid) ? lo : hi) = mid;
  }
  return ok(hi) ? make_optional(hi) : ok(lo) ? make_optional(lo) : nullopt;
}
