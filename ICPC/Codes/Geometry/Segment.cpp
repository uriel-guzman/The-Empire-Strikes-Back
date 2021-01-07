struct Seg {
  Pt a, b, ab;

  Seg(Pt a, Pt b) : a(a), b(b), ab(b - a) {}
  
  bool contains(Pt p) {
    // pointInSegment(a, b, p)
    return eq(ab.cross(p - a), 0) && leq((a - p).dot(b - p), 0);
  }

  int intersects(Seg s) {
    // intersectSegmentsInfo(a, b, c, d) 
    int t1 = sgn(v.cross(s.a - a)), t2 = sgn(v.cross(s.b - a));
    if (t1 == t2) 
      return t1 == 0 && (contains(s.a) || contains(s.b) || s.contains(a) || s.contains(b)) ? -1 : 0; 
    return sgn(s.v.cross(a - s.a)) != sgn(s.v.cross(b - s.a)); 
  }

  Pt intersection(Seg s) { 
    // Line.intersection(l), with a twist
    // always check intersects() first!
    Pt u1 = ab.unit(), u2 = s.ab.unit();
    return a + u1 * ((s.a - a).cross(u2) / u1.cross(u2));
  }
};