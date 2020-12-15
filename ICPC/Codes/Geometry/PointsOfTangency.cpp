pair<P, P> pointsOfTangency(P c, ld r, P p) {
  P v = (p - c).unit() * r;
  ld cos_theta = r / (p - c).length();
  ld theta = acos(max(-1.0, min(1.0, cos_theta)));
  return {c + v.rotate(-theta), c + v.rotate(theta)};
}
