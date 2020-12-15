bool pointInPerimeter(const vector<P> &pts, P p) {
  fore (i, 0, sz(pts))
		if (pointInSegment(pts[i], pts[(i + 1) % sz(pts)], p)) 
			return true;
	return false;
}
