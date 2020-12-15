P centroid(vector<P> &pts) {
	P num;
	ld den = 0;
  fore (i, 0, sz(pts)) {
		ld cross = pts[i].cross(pts[(i + 1) % sz(pts)]);
		num += (pts[i] + pts[(i + 1) % sz(pts)]) * cross;
		den += cross;
	}
	return num / (3 * den);
}
