ld distance(Pt p, Seg s) {
  if (le(p - s.a).dot(s.b - s.a), 0))
    return (p - s.a).length();
  if (le((p - s.b).dot(s.a - s.b), 0))
    return (p - s.b).length();
  return abs((s.a - p).cross(s.b - p) / (s.b - s.a).length());
}