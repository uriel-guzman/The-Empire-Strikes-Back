pair<P, double> getCircle(P m, P n, P p){
  P c = intersectLines((n + m) / 2, (n - m).perp(), (p + m) / 2, (p - m).perp());
  double r = (c - m).length();
  return {c, r};
}
