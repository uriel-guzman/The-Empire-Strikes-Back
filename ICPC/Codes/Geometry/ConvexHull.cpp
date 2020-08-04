vector<P> convexHull(vector<P> &pts) {
  int n = sz(pts);
  vector<P> low, up;
  sort(all(pts), [&](P a, P b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
  });
  pts.erase(unique(all(pts)), pts.end());
  if (n <= 2) 
    return pts;
  fore (i, 0, n) {
    while(sz(low) >= 2 && (low.end()[-1] - low.end()[-2]).cross(pts[i] - low.end()[-1]) <= 0)
      low.pop_back();
    low.pb(pts[i]);
  }
  fore (i, n, 0) {
    while(sz(up) >= 2 && (up.end()[-1] - up.end()[-2]).cross(pts[i] - up.end()[-1]) <= 0)
      up.pop_back();
    up.pb(pts[i]);
  }
  low.pop_back(), up.pop_back();
  low.insert(low.end(), all(up));
  return low;
}
