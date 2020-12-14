// log(n)
// first preprocess: seg = process(points)
// for each query: pointInConvexPolygon(seg, p - pts[0])
vector<P> process(const vector<P> &pts) {
  int n = sz(pts);
  rotate(pts.begin(), min_element(all(pts), [&](P a, P b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
  }), pts.end());
  vector<P> seg(n - 1);
  fore (i, 0, n - 1)
    seg[i] = pts[i + 1] - pts[0];
  return seg;
} 

bool pointInConvexPolygon(const vector<P> &seg, const P &p) {
  int n = sz(seg);
  if (neq(seg[0].cross(p), 0) && sgn(seg[0].cross(p)) != sgn(seg[0].cross(seg[n - 1])))
    return false;
  if (neq(seg[n - 1].cross(p), 0) && sgn(seg[n - 1].cross(p)) != sgn(seg[n - 1].cross(seg[0])))
    return false;
  if (eq(seg[0].cross(p), 0))
    return geq(seg[0].length(), p.length());
  int l = 0, r = n - 1;
  while (r - l > 1) {
    int m = l + ((r - l) >> 1);
    if (geq(seg[m].cross(p), 0)) 
      l = m;
    else
      r = m;
  }
  return eq(fabs(seg[l].cross(seg[l + 1])), fabs((p - seg[l]).cross(p - seg[l + 1])) + 
          fabs(p.cross(seg[l])) + fabs(p.cross(seg[l + 1])));
}
