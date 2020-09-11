bool isConvex(vector<P> pts) {
  int n = sz(pts);
  bool hasPos = false, hasNeg = false;
  fore (i, 0, n) {
    P first = pts[(i + 1) % n] - pts[i];
    P second = pts[(i + 2) % n] - pts[(i + 1) % n];
    double sign = first.cross(second);
    if (sign > 0) hasPos = true;
    if (sign < 0) hasNeg = true;
  }
  return !(hasPos && hasNeg);
}
