// point in convex polygon in O(log n)
// make sure that P is convex and in ccw
// before the queries, do the preprocess on P:
// rotate(P.begin(), min_element(P.begin(), P.end()), P.end());
// int right = max_element(P.begin(), P.end()) - P.begin();
// returns 0 if p is outside, 1 if p is inside, -1 if p is in the perimeter
//
int pointInConvexPolygon(const vector<P> &pts, P p, int right) {
	if (p < pts[0] || pts[right] < p)
    return 0;
	int orientation = sgn((pts[right] - pts[0]).cross(p - pts[0]));
	if (orientation == 0) {
		if (p == pts[0] || p == pts[right])
      return -1;
		return (right == 1 || right + 1 == sz(pts)) ? -1 : 1;
	} else if (orientation < 0) {
		auto r = lower_bound(pts.begin() + 1, pts.begin() + right, p);
		int det = sgn((p - r[-1]).cross(r[0] - r[-1])) - 1;
		return det == -2 ? 1 : det;
	} else {
		auto l = upper_bound(pts.rbegin(), pts.rend() - right - 1, p);
		int det = sgn((p - l[0]).cross((l == pts.rbegin() ? pts[0] : l[-1]) - l[0])) - 1;
		return det == -1 ? 1 : det;
	}
}
