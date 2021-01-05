int intersectSegmentsInfo(const P &a, const P &b, const P &c, const P &d) {
  P v1 = b - a, v2 = d - c;
  int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
  if (t == u) {
    if (t == 0) {
      if (PInSegment(a, b, c) || PInSegment(a, b, d) || PInSegment(c, d, a) || PInSegment(c, d, b))
        return -1; // infinity Ps
      else 
        return 0; // no P
    } else 
      return 0; // no P   
  } else 
      return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c)); // 1: single P 0: no P
}
