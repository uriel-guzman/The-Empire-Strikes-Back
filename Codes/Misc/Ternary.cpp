template <class T, class F>
pair<T, T> ternary(T lo, T hi, F f) {
  fore (it, 0, 234) {
    T m1 = lo + (hi - lo) / 3.0;
    T m2 = hi - (hi - lo) / 3.0;
    if (f(m1) <= f(m2))
      hi = m2;
    else
      lo = m1;
  }
  return min({make_pair(f(lo), lo),
              make_pair(f(lo + 1), lo + 1),
              make_pair(f(hi), hi)});
}
