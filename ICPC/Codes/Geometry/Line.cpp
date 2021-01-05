struct Line {
  P a, v;

  Line(P a, P b) : a(a), v((b - a).unit()) {}

  bool contains(P p) {
    // pointInLine(a, v, p)
    return eq((p - a).cross(v), 0);  
  }

  int intersects(Line l) { 
    // intersectLinesInfo(a1, v1, a2, v2)
    if (eq(v.cross(l.v), 0))
      return eq((l.a - a).cross(v), 0) ? -1 : 0;
    else 
      return 1;
  }

  bool parallel(Line l) {
    return eq(v.cross(l.v), 0);
  }

  P intersection(Line l) { 
    // intersectLines(a1, v1, a2, v2)
    // always check intersects() first!
    return a + v * ((l.a - a).cross(l.v) / v.cross(l.v));
  }

  P projection(P p) {
    return a + v * proj(p - a, v);
  }

  P reflection(P p) {
    return 2 * a - p + v * 2 * proj(p - a, v);
  }
};
