pair<lli, lli> crt(pair<lli, lli> a, pair<lli, lli> b) {
  if (a.s < b.s)
    swap(a, b);
  auto p = euclid(a.s, b.s);
  lli g = a.s * p.f + b.s * p.s, l = a.s / g * b.s;
  if ((b.f - a.f) % g != 0)
    return {-1, -1}; // no solution
  p.f = a.f + (b.f - a.f) % b.s * p.f % b.s / g * a.s;
  return {p.f + (p.f < 0) * l, l};
}
