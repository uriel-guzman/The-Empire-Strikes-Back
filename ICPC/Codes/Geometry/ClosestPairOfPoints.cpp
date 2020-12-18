pair<P, P> closestPairOfPoints(const vector<P> &pts) {
  sort(all(pts), [&](P a, P b) { return le(a.y, b.y); });
  set<P> st;
  ld ans = inf;
  P p, q;
  int pos = 0, n = sz(pts);
  fore(i, 0, n) {
    while (pos < i && geq(pts[i].y - pts[pos].y, ans))
      st.erase(pts[pos++]);
    auto lo = st.lower_bound(P{pts[i].x - ans - eps, -inf});
    auto hi = st.upper_bound(P{pts[i].x + ans + eps, -inf});
    for (auto it = lo; it != hi; ++it) {
      ld d = (pts[i] - *it).length();
      if (le(d, ans)) ans = d, p = pts[i], q = *it;
    }
    st.insert(pts[i]);
  }
  return {p, q};
}