struct Seg {
  Pt a, b, v;

  Seg() {}
  Seg(Pt a, Pt b) : a(a), b(b), v(b - a) {}

  bool contains(Pt p) {
    return eq(v.cross(p - a), 0) && leq((a - p).dot(b - p), 0);
  }

  int intersects(Seg s) {
    int d1 = a.dir(b, s.a), d2 = a.dir(b, s.b);
    if (d1 != d2)
      return s.a.dir(s.b, a) != s.a.dir(s.b, b);
    return d1 == 0 && (contains(s.a) || contains(s.b) || s.contains(a) || s.contains(b)) ? INF : 0;
  }

  template <class Seg>
  Pt intersection(Seg s) { // can be a line too
    return a + v * ((s.a - a).cross(s.v) / v.cross(s.v));
  }
};
