ld distance(Pt p, Line l) {
  Pt q = l.projection(p);
  return (p - q).length();
}