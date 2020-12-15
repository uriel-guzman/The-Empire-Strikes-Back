pair<P, ld> mec2(vector<P> &pts, P a, P b, int n) {
  ld hi = inf, lo = -hi;
  fore (i, 0, n) {
    ld si = (b - a).cross(pts[i] - a);
    if (eq(si, 0)) continue;
    P m = getCircle(a, b, pts[i]).f;
    ld cr = (b - a).cross(m - a);
    if (le(si, 0))
      hi = min(hi, cr);
    else
      lo = max(lo, cr);
  }
  ld v = (ge(lo, 0) ? lo : le(hi, 0) ? hi : 0);
  P c = (a + b) / 2 + (b - a).perp() * v / (b - a).norm();
  return {c, (a - c).norm()};
}

pair<P, ld> mec(vector<P> &pts, P a, int n) {
  random_shuffle(pts.begin(), pts.begin() + n);
  P b = pts[0], c = (a + b) / 2;
  ld r = (a - c).norm();
  for (int i = 1; i < n; ++i) 
    if (ge((pts[i] - c).norm(), r)) {
      tie(c, r) = (n == S.size() ? mec(pts, pts[i], i) : mec2(pts, a, pts[i], i));
    }
  return {c, r};
}

pair<P, ld> smallestEnclosingCircle(vector<P> pts) {
  assert(!pts.empty());
  auto r = mec(pts, pts[0], sz(pts));
  return {r.first, sqrt(r.second)};
}