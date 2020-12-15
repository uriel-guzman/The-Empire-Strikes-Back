pair<ld, ld> smallestEnclosingRectangle(vector<P> &pts) {
	int n = sz(pts);
	auto dot = [&](int a, int b){
    return (pts[(a + 1) % n] - pts[a]).dot(pts[(b + 1) % n] - pts[b]);
  };
	auto cross = [&](int a, int b){
    return (pts[(a + 1) % n] - pts[a]).cross(pts[(b + 1) % n] - pts[b]);
  };
	ld perimeter = inf, area = inf;
	for (int i = 0, j = 0, k = 0, m = 0; i < n; ++i) {
		while (ge(dot(i, j), 0))
      j = (j + 1) % n;
		if (!i)
      k = j;
		while (ge(cross(i, k), 0)) 
      k = (k + 1) % n;
		if (!i) 
      m = k;
		while (le(dot(i, m), 0)) 
      m = (m + 1) % n;
		//pairs: (i, k) , (j, m)
		point v = pts[(i + 1) % n] - pts[i];
		ld h = distancePointLine(pts[i], v, pts[k]);
		ld w = distancePointLine(pts[j], v.perp(), pts[m]);
		perimeter = min(perimeter, 2 * (h + w));
		area = min(area, h * w);
	}
	return {area, perimeter};
}
