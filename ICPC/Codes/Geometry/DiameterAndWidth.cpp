pair<ld, ld> diameterAndWidth(vector<P> &pts) {
	int n = sz(pts), k = 0;
	auto dot = [&](int a, int b) {
    return (pts[(a + 1) % n] - pts[a]).dot(pts[(b + 1) % n] - pts[b]);
  };
	auto cross = [&](int a, int b) { 
    return (pts[(a + 1) % n] - pts[a]).cross(pts[(b + 1) % n]-pts[b]);
  };
	ld diameter = 0, width = inf;
	while (ge(dot(0, k), 0))
    k = (k + 1) % n;
  fore (i, 0, n) {
		while (ge(cross(i, k), 0))
      k = (k + 1) % n;
		//pair: (i, k)
		diameter = max(diameter, (pts[k] - pts[i]).length());
		width = min(width, distancePointLine(pts[i], pts[(i + 1) % n] - pts[i], pts[k]));
	}
	return {diameter, width};
}
