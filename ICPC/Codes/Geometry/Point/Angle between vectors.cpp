double angleBetween(Pt a, Pt b) {
  double x = a.dot(b) / a.length() / b.length();
  return acosl(max(-1.0, min(1.0, x)));
}