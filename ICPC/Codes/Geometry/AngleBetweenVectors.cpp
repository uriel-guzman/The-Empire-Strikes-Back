double angleBetween(P a, P b) {
  double x = a.dot(b) / a.length() / b.length();
  return acos(max(-1.0, min(1.0, x)));
}
