struct Cir {
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

  vector<Pt> tangency(Pt p) {
    // pointsOfTangency
    // point outside the circle
    Pt v = (p - o).unit() * r;
    ld d2 = (p - o).norm(), d = sqrt(d2);
    if (leq(d, 0)) return {}; // on circle, no tangent
    Pt v1 = v * (r / d), v2 = v.perp() * (sqrt(d2 - r * r) / d);
    return {o + v1 - v2, o + v1 + v2};
  }

  vector<Pt> intersection(Cir c) { // by Retired_MiFaFaOvO
    ld d = (c.o - o).length();
    if (eq(d, 0)) return {}; // concentric circles
    if (ge(d, r + c.r)) return {}; // circles don't intersect
    Pt v = (c.o - o).unit();
    ld a = (r * r + d * d - c.r * c.r) / (2 * d);
    Pt p = o + v * a;
    if (eq(r + c.r, d)) return {p}; // circles touch at one point
    ld h = sqrt(r * r - a * a);
    Pt q = v.perp() * h;
    return {p - q, p + q}; // circles intersects twice
  }

  template <class L>
  vector<Pt> intersection(L l) {
    // for a segment you need to check that the point lies on the segment
    ld h2 = r * r - l.v.cross(o - l.a) * l.v.cross(o - l.a) / l.v.norm();
    Pt p = l.a + l.v * l.v.dot(o - l.a) / l.v.norm();
    if (eq(h2, 0)) return {p}; // line tangent to circle
    if (le(h2, 0)) return {}; // no intersection
    Pt q = l.v.unit() * sqrt(h2);
    return {p - q, p + q}; // two points of intersection (chord)
  }

  Cir get(Pt a, Pt b, Pt c) {
    // find circle that passes through points a, b, c
    Pt mab = (a + b) / 2, mcb = (b + c) / 2;
    Line ab(mab, mab + (b - a).perp());
    Line cb(mcb, mcb + (b - c).perp());
    Pt p = ab.intersection(cb);
    return Cir(p, (p - a).length());
  }

  ld commonArea(Cir c) {
    if (le(r, c.r))
      return c.commonArea(*this);
    ld d = (o - c.o).length();
    if (leq(d + c.r, r)) return c.r * c.r * pi;
    if (geq(d, r + c.r)) return 0.0;
    auto angle = [&](ld a, ld b, ld c) {
      return acos((a * a + b * b - c * c) / 2 / a / b);
    };
    auto cut = [&](ld a, ld r) {
      return (a - sin(a)) * r * r / 2;
    };
    ld a1 = angle(d, r, c.r);
    ld a2 = angle(d, c.r, r);
    return cut(a1 * 2, r) + cut(a2 * 2, c.r);
  }
};