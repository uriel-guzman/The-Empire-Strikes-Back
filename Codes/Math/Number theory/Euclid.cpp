pair<lli, lli> euclid(lli a, lli b) {
  if (b == 0) return {1, 0};
  auto p = euclid(b, a % b);
  return {p.s, p.f - a / b * p.s};
}