struct Cir {
  Pt o;
  ld r;
  Cir() {}
  Cir(ld x, ld y, ld r) : o(x, y), r(r) {}
  Cir(Pt o, ld r) : o(o), r(r) {}

  int inside(Cir c) {
    ld l = c.r - r - (o - c.o).length();
    return ge(l, 0) ? IN : eq(l, 0) ? ON : OVERLAP;
  }

  int outside(Cir c) {
    ld l = (o - c.o).length() - r - c.r;
    return ge(l, 0) ? OUT : eq(l, 0) ? ON : OVERLAP;
  }

  int contains(Pt p) {
    ld l = (p - o).length() - r;
    return le(l, 0) ? IN : eq(l, 0) ? ON : OUT;
  }

  Pt projection(Pt p) {
    return o + (p - o).unit() * r;
  }

  vector<Pt> tangency(Pt p) {
    // point outside the circle
    Pt v = (p - o).unit() * r;
    ld d2 = (p - o).norm(), d = sqrt(d2);
    if (leq(d, 0)) return {}; // on circle, no tangent
    Pt v1 = v * (r / d), v2 = v.perp() * (sqrt(d2 - r * r) / d);
    return {o + v1 - v2, o + v1 + v2};
  }

  vector<Pt> intersection(Cir c) { 
    ld d = (c.o - o).length();
    if (eq(d, 0) || ge(d, r + c.r) || le(d, abs(r - c.r))) return {}; // circles don't intersect
    Pt v = (c.o - o).unit();
    ld a = (r * r + d * d - c.r * c.r) / (2 * d);
    Pt p = o + v * a;
    if (eq(d, r + c.r) || eq(d, abs(r - c.r))) return {p}; // circles touch at one point
    ld h = sqrt(r * r - a * a);
    Pt q = v.perp() * h;
    return {p - q, p + q}; // circles intersects twice
  }

  template <class Line>
  vector<Pt> intersection(Line l) {
    // for a segment you need to check that the point lies on the segment
    ld h2 = r * r - l.v.cross(o - l.a) * l.v.cross(o - l.a) / l.v.norm();
    Pt p = l.a + l.v * l.v.dot(o - l.a) / l.v.norm();
    if (eq(h2, 0)) return {p}; // line tangent to circle
    if (le(h2, 0)) return {}; // no intersection
    Pt q = l.v.unit() * sqrt(h2);
    return {p - q, p + q}; // two points of intersection (chord)
  }

  Cir(Pt a, Pt b, Pt c) {
    // find circle that passes through points a, b, c
    Pt mab = (a + b) / 2, mcb = (b + c) / 2;
    Seg ab(mab, mab + (b - a).perp());
    Seg cb(mcb, mcb + (b - c).perp());
    o = ab.intersection(cb);
    r = (o - a).length();
  }

  ld commonArea(Cir c) {
    if (le(r, c.r))
      return c.commonArea(*this);
    ld d = (o - c.o).length();
    if (leq(d + c.r, r)) return c.r * c.r * pi;
    if (geq(d, r + c.r)) return 0.0;
    auto angle = [&](ld a, ld b, ld c) {
      return acos((a * a + b * b - c * c) / (2 * a * b));
    };
    auto cut = [&](ld a, ld r) {
      return (a - sin(a)) * r * r / 2;
    };
    ld a1 = angle(d, r, c.r), a2 = angle(d, c.r, r);
    return cut(a1 * 2, r) + cut(a2 * 2, c.r);
  }
};
