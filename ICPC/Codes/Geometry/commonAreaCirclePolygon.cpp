ld commonArea(const Cir &c, const Poly &poly) {
  auto arg = [&](Pt p, Pt q) {
    return atan2(p.cross(q), p.dot(q));
  };
  auto tri = [&](Pt p, Pt q) {
    Pt d = q - p;
    ld a = d.dot(p) / d.norm(), b = (p.norm() - c.r * c.r) / d.norm();
    ld det = a * a - b;
    if (leq(det, 0)) return arg(p, q) * c.r * c.r;
    ld s = max(0.L, -a - sqrt(det)), t = min(1.L, -a + sqrt(det));
    if (t < 0 || 1 <= s) return arg(p, q) * c.r * c.r;
    Pt u = p + d * s, v = p + d * t;
    return u.cross(v) + (arg(p, u) + arg(v, q)) * c.r * c.r;
  };
  ld sum = 0;
  fore (i, 0, sz(poly))
    sum += tri(poly[i] - c.o, poly[(i + 1) % sz(poly)] - c.o);
  return abs(sum / 2);
}