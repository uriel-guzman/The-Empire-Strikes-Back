bool isConvex(const Poly& pts) {
  int n = sz(pts);
  bool pos = 0, neg = 0;
  fore (i, 0, n) {
    Pt a = pts[(i + 1) % n] - pts[i];
    Pt b = pts[(i + 2) % n] - pts[(i + 1) % n];
    int dir = sgn(a.cross(b));
    if (dir > 0)
      pos = 1;
    if (dir < 0)
      neg = 1;
  }
  return !(pos && neg);
}