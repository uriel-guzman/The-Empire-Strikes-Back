double angleBetween(P a, P b) {
  double x = a.dot(b) / a.length() / b.length();
  return acos(max(ld(-1.0), min(ld(1.0), ld(x))));
}
