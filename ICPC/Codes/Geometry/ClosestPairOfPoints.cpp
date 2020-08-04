pair<P, P> cpp(vector<P> points) {
  sort(all(points), [&](P a, P b) {
    return le(a.y, b.y);
  });
  set<P> st;
  ld ans = inf;
  P p, q;
  int pos = 0, n = sz(points);
  fore (i, 0, n) {
    while (pos < i && geq(points[i].y - points[pos].y, ans)) 
      st.erase(points[pos++]);
    auto lo = st.lower_bound({points[i].x - ans - eps, -inf});
    auto hi = st.upper_bound({points[i].x + ans + eps, -inf});
    for (auto it = lo; it != hi; ++it) {
      ld d = (points[i] - *it).length();
      if (le(d, ans)) 
        ans = d, p = points[i], q = *it;
    }
    st.insert(points[i]);
  }
  return {p, q};
}
