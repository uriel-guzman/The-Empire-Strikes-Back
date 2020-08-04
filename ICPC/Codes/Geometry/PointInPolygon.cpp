int pointInPolygon(const vector<P> &points, P p) { // O(N)
	int n = sz(points), ans = 0;
	fore (i, 0, n) {
		P a = points[i], b = points[(i + 1) % n];
		if (pointInSegment(a, b, p)) 
      return -1; // on perimeter
		if (a.y > b.y) 
      swap(a,b);
		if (a.y <= p.y && b.y > p.y && (a - p).cross(b - p) > 0) 
      ans ^= 1;
	}
	return ans ? 1 : 0; // inside, outside
}
