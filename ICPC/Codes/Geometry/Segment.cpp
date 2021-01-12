struct Seg {
  Pt a, b, v;

  Seg() {}
  Seg(Pt a, Pt b) : a(a), b(b), v(b - a) {}
  
  bool contains(Pt p) {
    return eq(v.cross(p - a), 0) && leq((a - p).dot(b - p), 0);
  }

  int intersects(Seg s) {
    int t1 = sgn(v.cross(s.a - a)), t2 = sgn(v.cross(s.b - a));
    if (t1 == t2) 
      return t1 == 0 && (contains(s.a) || contains(s.b) || s.contains(a) || s.contains(b)) ? -1 : 0; 
    return sgn(s.v.cross(a - s.a)) != sgn(s.v.cross(b - s.a)); 
  }

  template <class T>
  Pt intersection(T t) { 
    return a + v * ((t.a - a).cross(t.v) / v.cross(t.v));
  }
};
