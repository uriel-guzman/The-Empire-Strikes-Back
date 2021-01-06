pair<Pt, Pt> closestPairOfPoints(const Poly &pts) {
  sort(all(pts), [&](Pt a, Pt b) { 
    return le(a.y, b.y); 
  });
  set<Pt> st;
  ld ans = inf;
  Pt p, q;
  int pos = 0, n = sz(pts);
  fore(i, 0, n) {
    while (pos < i && geq(pts[i].y - pts[pos].y, ans))
      st.erase(pts[pos++]);
    auto lo = st.lower_bound(Pt{pts[i].x - ans - eps, -inf});
    auto hi = st.upper_bound(Pt{pts[i].x + ans + eps, -inf});
    for (auto it = lo; it != hi; ++it) {
      ld d = (pts[i] - *it).length();
      if (le(d, ans)) 
        ans = d, p = pts[i], q = *it;
    }
    st.insert(pts[i]);
  }
  return {p, q};
}
