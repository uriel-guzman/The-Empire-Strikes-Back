struct Seg {
  Pt a, b, ab;

  Seg(Pt a, Pt b) : a(a), b(b), ab(b - a) {}
  
  bool contains(Pt p) {
    // pointInSegment(a, b, p)
    return eq(ab.cross(p - a), 0) && leq((a - p).dot(b - p), 0);
  }

  int intersects(Seg s) {
    // intersectSegmentsInfo(a, b, c, d) 
    // DONT WORK :c
    int t = sgn(ab.cross(s.a - a)), u = sgn(ab.cross(s.b - a));
    if (t == u) 
      return t == 0 && (contains(s.a) || contains(s.b) || s.contains(a) || s.contains(b)) ? -1 : 0; 
    return sgn(s.ab.cross(a - s.a)) != sgn(s.ab.cross(b - s.a)); 
  }

  Pt intersection(Seg s) { 
    // Line.intersection(l), with a twist
    if (intersects(s) != 1)
      return Pt(NAN, NAN);
    Pt u1 = ab.unit(), u2 = s.ab.unit();
    return a + u1 * ((s.a - a).cross(u2) / u1.cross(u2));
  }
};