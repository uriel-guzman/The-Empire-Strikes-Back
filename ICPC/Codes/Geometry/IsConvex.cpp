bool isConvex(vector<P> points) {
  int n = sz(points);
  bool hasPos = false, hasNeg = false;
  fore (i, 0, n) {
    P first = points[(i+1)%n] - points[i];
    P second = points[(i+2)%n] - points[(i+1)%n];
    double sign = first.cross(second);
    if (sign > 0) hasPos = true;
    if (sign < 0) hasNeg = true;
  }
  return !(hasPos && hasNeg);
}
