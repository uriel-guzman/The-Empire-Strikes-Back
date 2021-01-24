ld distancePointCircle(P c, ld r, P p) {
	//point p, circle with center c and radius r
	return max((ld)0, (p - c).length() - r);
}
