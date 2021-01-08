int pointInPolygon(const Poly &pts, Pt p) {
  int n = sz(pts);
  int rays = 0;
  fore (i, 0, n) {
    Pt a = pts[i], b = pts[(i + 1) % n];
    if (ge(a.y, b.y)) 
      swap(a, b);
    if (Seg(a, b).contains(p))
      return -1;
    rays ^= (leq(a.y, p.y) && le(p.y, b.y) && ge((a - p).cross(b - p), 0));
  } 
  return rays & 1;
}
