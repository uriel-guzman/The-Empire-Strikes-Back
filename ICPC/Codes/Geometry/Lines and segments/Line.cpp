struct Line {
  Pt a, b, v;

  Line() {}
  Line(Pt a, Pt b) : a(a), b(b), v((b - a).unit()) {}

  bool contains(Pt p) {
    return eq((p - a).cross(b - a), 0);
  }

  int intersects(Line l) {
    if (eq(v.cross(l.v), 0))
      return eq((l.a - a).cross(v), 0) ? INF : 0;
    return 1;
  }

  int intersects(Seg s) {
    if (eq(v.cross(s.v), 0))
      return eq((s.a - a).cross(v), 0) ? INF : 0;
    return a.dir(b, s.a) != a.dir(b, s.b);
  }

  template <class Line>
  Pt intersection(Line l) { // can be a segment too
    return a + v * ((l.a - a).cross(l.v) / v.cross(l.v));
  }

  Pt projection(Pt p) {
    return a + v * proj(p - a, v);
  }

  Pt reflection(Pt p) {
    return a * 2 - p + v * 2 * proj(p - a, v);
  }
};