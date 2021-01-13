ld distance(Pt p, Cir c) {
  // distancePointCircle
  return max(ld(0), (p - c.o).length() - c.r);
}