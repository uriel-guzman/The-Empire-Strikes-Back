int pointInCircle(P c, ld r, P & p) {
	//test if point p is inside the circle with center c and radius r
	//returns "0" if it's outside, "-1" if it's in the perimeter, "1" if it's inside
	ld l = (p - c).length() - r;
	return (le(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}
