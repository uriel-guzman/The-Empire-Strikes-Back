Cir minEnclosing(vector<Pt>& pts) { // a bunch of points
  shuffle(all(pts), rng);
  Cir c(0, 0, 0);
  fore (i, 0, sz(pts))
    if (!c.contains(pts[i])) {
      c = Cir(pts[i], 0);
      fore (j, 0, i)
        if (!c.contains(pts[j])) {
          c = Cir((pts[i] + pts[j]) / 2, (pts[i] - pts[j]).length() / 2);
          fore (k, 0, j)
            if (!c.contains(pts[k]))
              c = Cir(pts[i], pts[j], pts[k]);
        }
    }
  return c;
}