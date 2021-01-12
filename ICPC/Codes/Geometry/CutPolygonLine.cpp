Poly cut(const Poly &pts, Line l) {
  Poly ans;
  int n = sz(pts);
  fore (i, 0, n) {
    int j = (i + 1) % n;
    if (geq(l.v.cross(pts[i] - l.a), 0)) // left
      ans.pb(pts[i]);
    Seg s(pts[i], pts[j]);
    if (l.intersects(s) == 1) {
      Pt p = l.intersection(s);
      if (p != pts[i] && p != pts[j])
        ans.pb(p);
    }
  }
  return ans;
}
