// -1 : perimeter, 0: outside, 1 if inside
int pointInCircle(const P &c, ld r, const P &p) {
  ld l = (p - c).length() - r;
  return (le(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}

bool pointInCircle(const P &c, ld r, const P &p) {
  return sq(p.x - c.x) + sq(p.y - c.y) <= sq(r);
}
