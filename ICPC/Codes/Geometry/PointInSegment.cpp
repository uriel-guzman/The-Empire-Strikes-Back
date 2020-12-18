bool pointInSegment(P a, P b, P p) {
  return eq((b - a).cross(p - a), 0) && leq((a - p).dot(b - p), 0);
}