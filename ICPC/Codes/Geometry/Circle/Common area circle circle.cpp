ld commonArea(Cir a, Cir b) {
  if (le(a.r, b.r))
    swap(a, b);
  ld d = (a - b).length();
  if (leq(d + b.r, a.r))
    return b.r * b.r * PI;
  if (geq(d, a.r + b.r))
    return 0.0;
  auto angle = [&](ld x, ld y, ld z) {
    return acos((x * x + y * y - z * z) / (2 * x * y));
  };
  auto cut = [&](ld x, ld r) {
    return (x - sin(x)) * r * r / 2;
  };
  ld a1 = angle(d, a.r, b.r), a2 = angle(d, b.r, a.r);
  return cut(a1 * 2, a.r) + cut(a2 * 2, b.r);
}