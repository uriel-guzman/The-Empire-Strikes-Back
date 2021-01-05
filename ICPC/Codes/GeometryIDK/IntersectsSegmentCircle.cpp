vector<P> intersectSegmentCircle(P a, P b, P c, ld r) {
	//segment ab, circle with center c and radius r
	vector<P> pts = intersectLineCircle(a, b - a, c, r), ans;
	for (P p : pts) 
		if (pointInSegment(a, b, p)) 
      ans.pb(p);
	return ans;
}
