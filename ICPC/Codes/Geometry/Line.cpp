struct Line {
  Pt a, v;

  Line(Pt a, Pt b) : a(a), v((b - a).unit()) {}

  bool contains(Pt p) {
    // pointInLine(a, v, p)
    return eq((p - a).cross(v), 0);  
  }

  int intersects(Line l) { 
    // intersectLinesInfo(a1, v1, a2, v2)
    if (eq(v.cross(l.v), 0))
      return eq((l.a - a).cross(v), 0) ? -1 : 0;
    return 1;
  }

  bool parallel(Line l) {
    return eq(v.cross(l.v), 0);
  }

  Pt intersection(Line l) { 
    // intersectLines(a1, v1, a2, v2)
    // always check intersects() first!
    return a + v * ((l.a - a).cross(l.v) / v.cross(l.v));
  }

  Pt projection(Pt p) {
    return a + v * proj(p - a, v);
  }

  Pt reflection(Pt p) {
    return a * 2 - p + v * 2 * proj(p - a, v);
  }
};
