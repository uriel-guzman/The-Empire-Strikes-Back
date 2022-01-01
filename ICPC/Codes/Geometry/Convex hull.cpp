vector<Pt> convexHull(vector<Pt> pts) {
  vector<Pt> hull;
  sort(all(pts), [&](Pt a, Pt b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
  });
  pts.erase(unique(all(pts)), pts.end());
  fore (i, 0, sz(pts)) {
    while (sz(hull) >= 2 && hull.back().dir(pts[i], hull[sz(hull) - 2]) < 0)
      hull.pop_back();
    hull.pb(pts[i]);
  }
  hull.pop_back();
  int k = sz(hull);
  for (int i = sz(pts) - 1; i >= 0; i--) {
    while (sz(hull) >= k + 2 && hull.back().dir(pts[i], hull[sz(hull) - 2]) < 0)
      hull.pop_back();
    hull.pb(pts[i]);
  }
  hull.pop_back();
  return hull;
}