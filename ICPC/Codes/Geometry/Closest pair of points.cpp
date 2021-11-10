pair<Pt, Pt> closestPairOfPoints(vector<Pt> &pts) {
  sort(all(pts), [&](Pt a, Pt b) {
    return le(a.x, b.x); 
  });
  // set sorted by smaller y coordinate
  set<Pt> st;
  ld ans = INF;
  Pt p, q;
  int pos = 0;
  fore (i, 0, sz(pts)) {
    while (pos < i && geq(pts[i].x - pts[pos].x, ans))
      st.erase(pts[pos++]);
    auto lo = st.lower_bound(Pt(-INF, pts[i].y - ans - EPS));
    auto hi = st.upper_bound(Pt(-INF, pts[i].y + ans + EPS));
    for (auto it = lo; it != hi; ++it) {
      ld d = (pts[i] - *it).length();
      if (le(d, ans)) 
        ans = d, p = pts[i], q = *it;
    }
    st.insert(pts[i]);
  }
  return {p, q};
}