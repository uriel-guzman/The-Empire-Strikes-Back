//returns the part of the convex polygon P on the left side of line a+tv
vector<P> cutPolygon(const vector<P> &pts, P a, P v) {
	vector<P> lhs;
  fore (i, 0, sz(pts)) {
		if (geq(v.cross(pts[i] - a), 0))
			lhs.push_back(pts[i]);
		if (intersectLineSegmentInfo(a, v, pts[i], pts[(i + 1) % sz(pts)]) == 1) {
			P p = intersectLines(a, v, pts[i], pts[(i + 1) % sz(pts)] - pts[i]);
			if (p != pts[i] && p != pts[(i + 1) % sz(pts)]) 
				lhs.push_back(p);
		}
	}
	return lhs;
}
