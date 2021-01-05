vector<P> intersectLineCircle(const P &a, const P &v, const P &c, ld r) {
  ld h2 = r * r - v.cross(c - a) * v.cross(c - a) / v.norm();
  P p = a + v * v.dot(c - a) / v.norm();
  if (eq(h2, 0))
    return {p};  // line tangent to circle
  else if (le(h2, 0))
    return {};  // no intersection
  else {
    point u = v.unit() * sqrt(h2);
    return {p - u, p + u};  // two points of intersection (chord)
  }
}
bool pointInLine(const P &a, const P &v, const P &p) {
  return eq((p - a).cross(v), 0);
}
bool pointInSegment(const P &a, const P &b, const P &p) {
  return pointInLine(a, b - a, p) && leq((a - p).dot(b - p), 0);
}
int pointInCircle(const P &c, ld r, const P &p) {
  ld l = (p - c).length() - r;
  return (le(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}
vector<P> intersectSegmentCircle(const P &a, const P &b, const point &c, ld r) {
  vector<P> points = intersectLineCircle(a, b - a, c, r), ans;
  for (const P &p : points) {
    if (pointInSegment(a, b, p)) ans.pb(p);
  }
  return ans;
}
ld signed_angle(const P &a, const P &b) {
  return sgn(a.cross(b)) * acosl(a.dot(b) / (a.length() * b.length()));
}
ld intersectPolygonCircle(const vector<P> &points, const P &c, ld r) {
  int n = points.size();
  ld ans = 0;
  for (int i = 0; i < n; ++i) {
    P p = points[i], q = points[(i + 1) % n];
    bool p_inside = (pointInCircle(c, r, p) != 0);
    bool q_inside = (pointInCircle(c, r, q) != 0);
    if (p_inside && q_inside) {
      ans += (p - c).cross(q - c);
    } else if (p_inside && !q_inside) {
      P s1 = intersectSegmentCircle(p, q, c, r)[0];
      P s2 = intersectSegmentCircle(c, q, c, r)[0];
      ans += (p - c).cross(s1 - c) + r * r * signed_angle(s1 - c, s2 - c);
    } else if (!p_inside && q_inside) {
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
