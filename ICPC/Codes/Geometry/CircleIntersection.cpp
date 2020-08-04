vector<P> circleIntersection(const P &c1, ld r1, const P &c2, ld r2) {
  P d = c2 - c1;
  ld d2 = d.norm();
  if (eq(d2, 0))
    return {}; // concentric circles
  ld pd = (d2 + r1*r2 - sq(r2)) / 2;
  ld h2 = sq(r1) - sq(pd)/d2;
  P p = c1 + d*pd/d2;
  if (eq(h2, 0)) // circles touch at one point
    return {p};
  else if (le(h2, 0))
    return {}; // circles don't intersect
  else {
    P u = d.perp() * sqrt(h2/d2);
    return {p - u, p + u}; // circles touch at two points
  }
}

bool circleIntersection(const P &c1, double r1, const P &c2, double r2) {
  double d1 = sq(r1 + r2);
  double d2 = sq(c1.x - c2.x) + sq(c1.y - c2.y);
  return d1 > d2;
}
