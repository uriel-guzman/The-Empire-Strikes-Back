struct Cir {
  #define sq(x) (x) * (x)
  Pt o;
  ld r;
  Cir() {}
  Cir(ld x, ld y, ld r) : o(x, y), r(r) {}
  Cir(Pt o, ld r) : o(o), r(r) {}

  int inside(Cir c) {
    // circleInsideCircle
    // -1: internally, 0: overlap, 1: inside
    ld l = r - c.r - (o - c.o).length();
    return ge(l, 0) ? 1 : eq(l, 0) ? -1 : 0;
  }

  int outside(Cir c) {
    // circleOutsideCircle
    // -1: externally, 0: overlap, 1: outside
    ld l = (o - c.o).length() - r - c.r;
    return ge(l, 0) ? 1 : eq(l, 0) ? -1 : 0;
  }

  int contains(Pt p) {
    // pointInCircle
    // -1: perimeter, 0: outside, 1: inside
    ld l = (p - o).length() - r;
    return le(l, 0) ? 1 : eq(l, 0) ? -1 : 0;
  }

  Pt projection(Pt p) {
    // projectionPointCircle
    // point outside the circle
    return o + (p - o).unit() * r;
  }

  pair<Pt, Pt> tangency(Pt p) {
    // pointsOfTangency
    // point outside the circle
    Pt v = (p - o).unit() * r;
    ld d2 = (p - o).norm(), d = sqrt(d2);
    Pt v1 = v * (r / d), v2 = v.perp() * (sqrt(d2 - r * r) / d);
    return {o + v1 - v2, o + v1 + v2};
  }

  vector<Pt> intersection(Cir c) {
    // intersectionCircles
    Pt d = c.o - o;
    ld d2 = d.norm();
    if (eq(d2, 0)) return {}; // concentric circles
    ld pd = (d2 + r * r - c.r * c.r) / 2;
    ld h2 = r * r - pd * pd / d2;
    Pt p = o + d * pd / d2;
    if (eq(h2, 0)) return {p}; // circles touch at one point
    if (le(h2, 0)) return {}; // circles don't intersect
    Pt u = d.perp() * sqrt(h2 / d2);
    return {p - u, p + u}; // circles intersects twice
  }

  template <class T>
  vector<Pt> intersection(T t) {
    // intersectLineCircle and intersectSegmentCircle
    // for a segment you need to check that the point lies on the segment
    ld h2 = sq(r) - sq(t.v.cross(o - t.a)) / t.v.norm();
    Pt p = t.a + t.v * t.v.dot(o - t.a) / t.v.norm();
    if (eq(h2, 0)) return {p}; // line tangent to circle
    if (le(h2, 0)) return {}; // no intersection
    Pt u = t.v.unit() * sqrt(h2);
    return {p - u, p + u}; // two points of intersection (chord)
  }

  Cir get(Pt a, Pt b, Pt c) {
    // find circle that passes through points a, b, c
    Pt mab = (a + b) / 2, mcb = (b + c) / 2;
    Line ab(mab, mab + (b - a).perp());
    Line cb(mcb, mcb + (b - c).perp());
    Pt p = ab.intersection(cb);
    return Cir(p, (p - a).length());
  }
};