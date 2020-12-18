bool crossesRay(P a, P b, P p) {
	return (geq(b.y, p.y) - geq(a.y, p.y)) * sgn((a - p).cross(b - p)) > 0;
}

int pointInPolygon(const vector<P> &pts, P p) {
  if (pointInPerimeter(pts, p)) 
    return -1;  // point in the perimeter
  int rays = 0;
  fore(i, 0, sz(pts)) 
    rays += crossesRay(pts[i], pts[(i + 1) % sz(pts)], p);
  return rays & 1;  // 0: point outside, 1: point inside
}
