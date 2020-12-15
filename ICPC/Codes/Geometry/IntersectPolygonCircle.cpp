ld intersectPolygonCircle(const vector<P>& pts, P c, ld r) {
  // Gets the area of the intersection of the polygon with the circle
  int n = sz(pts);
  ld ans = 0;
  fore (i, 0, n) {
    P p = pts[i], q = pts[(i + 1) % n];
    bool pInside = (pointInCircle(c, r, p) != 0);
    bool qInside = (pointInCircle(c, r, q) != 0);
    if (pInside && qInside) {
      ans += (p - c).cross(q - c);
    } else if (pInside && !qInside) {
      P s1 = intersectSegmentCircle(p, q, c, r)[0];
      P s2 = intersectSegmentCircle(c, q, c, r)[0];
      ans += (p - c).cross(s1 - c) + r * r * signed_angle(s1 - c, s2 - c);
    } else if (!pInside && qInside) {
      P s1 = intersectSegmentCircle(c, p, c, r)[0];
      P s2 = intersectSegmentCircle(p, q, c, r)[0];
      ans += (s2 - c).cross(q - c) + r * r * signed_angle(s1 - c, s2 - c);
    } else {
      auto info = intersectSegmentCircle(p, q, c, r);
      if (info.size() <= 1) {
        ans += r * r * signed_angle(p - c, q - c);
      } else {
        P s2 = info[0], s3 = info[1];
        P s1 = intersectSegmentCircle(c, p, c, r)[0];
        P s4 = intersectSegmentCircle(c, q, c, r)[0];
        ans += (s2 - c).cross(s3 - c) + r * r * (signed_angle(s1 - c, s2 - c) + signed_angle(s3 - c, s4 - c));
      }
    }
  }
  return abs(ans) / 2;
}
