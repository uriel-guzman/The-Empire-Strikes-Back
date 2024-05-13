struct Cir : Pt {
  ld r;
  Cir() {}
  Cir(ld x, ld y, ld r) : Pt(x, y), r(r) {}
  Cir(Pt p, ld r) : Pt(p), r(r) {}

  int inside(Cir c) {
    ld l = c.r - r - (*this - c).length();
    return ge(l, 0) ? IN : eq(l, 0) ? ON : OVERLAP;
  }

  int outside(Cir c) {
    ld l = (*this - c).length() - r - c.r;
    return ge(l, 0) ? OUT : eq(l, 0) ? ON : OVERLAP;
  }

  int contains(Pt p) {
    ld l = (p - *this).length() - r;
    return le(l, 0) ? IN : eq(l, 0) ? ON : OUT;
  }

  Pt projection(Pt p) {
    return *this + (p - *this).unit() * r;
  }

  vector<Pt> tangency(Pt p) { // point outside the circle
    Pt v = (p - *this).unit() * r;
    ld d2 = (p - *this).norm(), d = sqrt(d2);
    if (leq(d, 0))
      return {}; // on circle, no tangent
    Pt v1 = v * (r / d);
    Pt v2 = v.perp() * (sqrt(d2 - r * r) / d);
    return {*this + v1 - v2, *this + v1 + v2};
  }

  vector<Pt> intersection(Cir c) {
    ld d = (c - *this).length();
    if (eq(d, 0) || ge(d, r + c.r) || le(d, abs(r - c.r)))
      return {}; // circles don't intersect
    Pt v = (c - *this).unit();
    ld a = (r * r + d * d - c.r * c.r) / (2 * d);
    Pt p = *this + v * a;
    if (eq(d, r + c.r) || eq(d, abs(r - c.r)))
      return {p}; // circles touch at one point
    ld h = sqrt(r * r - a * a);
    Pt q = v.perp() * h;
    return {p - q, p + q}; // circles intersects twice
  }

  template <class Line>
  vector<Pt> intersection(Line l) {
    // for a segment you need to check that the point lies on the segment
    ld h2 =
        r * r - l.v.cross(*this - l.a) * l.v.cross(*this - l.a) / l.v.norm();
    Pt p = l.a + l.v * l.v.dot(*this - l.a) / l.v.norm();
    if (eq(h2, 0))
      return {p}; // line tangent to circle
    if (le(h2, 0))
      return {}; // no intersection
    Pt q = l.v.unit() * sqrt(h2);
    return {p - q, p + q}; // two points of intersection (chord)
  }

  Cir(Pt a, Pt b, Pt c) {
    // find circle that passes through points a, b, c
    Pt mab = (a + b) / 2, mcb = (b + c) / 2;
    Seg ab(mab, mab + (b - a).perp());
    Seg cb(mcb, mcb + (b - c).perp());
    Pt o = ab.intersection(cb);
    *this = Cir(o, (o - a).length());
  }
};
