template <class T, class F>
T tern(T lo, T hi, F f) {
  T m1 = lo + (hi - lo) / 3.0;
  T m2 = hi - (hi - lo) / 3.0;

  if (f(m1) <= f(m2))
    hi = m2;
  else
    lo = m1;

  return min(f(m1), f(m2));
}
